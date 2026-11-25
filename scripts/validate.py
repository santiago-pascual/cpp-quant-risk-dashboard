"""Independent pandas/NumPy reference; compare all scalar and exported series."""
import argparse
from pathlib import Path
import subprocess
import tempfile
import numpy as np
import pandas as pd


def validate(exe, source, periods, rf, confidence, window, figures=None):
    df = pd.read_csv(source)
    dates = pd.to_datetime(df.Date)
    p = pd.Series(df['Close' if 'Close' in df else 'Close/Last'].astype(str).str.replace('$', '', regex=False).astype(float).values, index=dates).sort_index()
    r = p.pct_change().dropna(); logs = np.log(p).diff().dropna()
    periodic = np.expm1(np.log1p(rf)/periods)
    sd = r.std(); down = np.sqrt(np.minimum(r-periodic, 0).pow(2).mean())
    dd = 1-p/p.cummax(); rolling = r.rolling(window).std()*np.sqrt(periods)
    loss = np.sort(-r.to_numpy()); n = len(r); mass = (1-confidence)*n
    weights = np.clip(mass-np.arange(n), 0, 1)
    ref = dict(mean_simple=r.mean(), mean_log=logs.mean(), geometric_return=np.expm1(logs.mean()), sample_variance=r.var(), volatility=sd, annual_volatility=sd*np.sqrt(periods), annual_arithmetic=r.mean()*periods, annual_geometric=np.expm1(logs.mean()*periods), calendar_cagr=np.expm1(logs.sum()*365.2425/(p.index[-1]-p.index[0]).days), sharpe=(r.mean()-periodic)*np.sqrt(periods)/sd if sd>0 else np.nan, sortino=(r.mean()-periodic)*np.sqrt(periods)/down if down>0 else np.nan, downside_deviation=down, max_drawdown=dd.max(), var=loss[int(np.ceil(confidence*n))-1], es=np.dot(loss[::-1],weights)/mass)
    with tempfile.TemporaryDirectory() as tmp:
        out=Path(tmp)/'out.csv'
        result=subprocess.check_output([str(Path(exe).resolve()),str(source),'--periods',str(periods),'--rf',str(rf),'--confidence',str(confidence),'--window',str(window),'--export',str(out)],text=True)
        actual={k:float(v) if v!='N/A' else np.nan for k,v in (line.split('=') for line in result.splitlines())}
        assert actual.keys()==ref.keys()
        for k,v in ref.items(): np.testing.assert_allclose(actual[k],v,rtol=1e-10,atol=1e-12,equal_nan=True,err_msg=k)
        export=pd.read_csv(out,parse_dates=['date']).set_index('date')
        np.testing.assert_array_equal(export.index,p.index)
        for k,v in dict(price=p,simple_return=r,log_return=logs,drawdown=dd,rolling_volatility=rolling).items(): np.testing.assert_allclose(export[k],v.reindex(p.index),rtol=1e-10,atol=1e-12,equal_nan=True,err_msg=k)
    print(f'{source}: {len(ref)} scalar metrics and {len(p)} rows x 5 series passed')
    if figures:
        import matplotlib.pyplot as plt
        figures.mkdir(exist_ok=True)
        for name,series,title in [('returns',r,'Synthetic historical simple returns'),('rolling_volatility',rolling,'Trailing annualized volatility'),('drawdown',dd,'Peak-to-trough drawdown')]:
            fig,ax=plt.subplots(figsize=(9,3.5)); ax.plot(series.index,series*100); ax.set(title=title,ylabel='Percent'); ax.grid(alpha=.25); fig.autofmt_xdate(); fig.tight_layout(); fig.savefig(figures/f'{name}.png',dpi=150); plt.close(fig)
        print('| Metric | C++ | Python |\n|---|---:|---:|')
        for k,v in ref.items(): print(f'| {k} | {actual[k]:.10g} | {v:.10g} |')

if __name__=='__main__':
    ap=argparse.ArgumentParser(); ap.add_argument('exe'); ap.add_argument('--figures',action='store_true'); args=ap.parse_args()
    root=Path(__file__).resolve().parents[1]
    validate(args.exe,root/'data/synthetic_prices.csv',365,.03,.95,20,root/'figures' if args.figures else None)
    validate(args.exe,root/'HistoricalData_1795299932817.csv',252,.02,.90,5)
