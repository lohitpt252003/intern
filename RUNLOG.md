# Run log

| Profile | Delay (ms) | Miss rate | Overhead | Change / observation |
|---|---:|---:|---:|---|
| A_mild | 150 | 0.00% (0/400) | 1.55x | First coded try, 8 s. The 4-data/2-parity scheme was valid. |
| B_moderate | 160 | 0.00% (0/600) | 1.55x | Tried it on the higher loss and jitter profile for 12 s. This is the delay I picked for grading. |

Commands used: `make && python3 run.py --profile profiles/A.json --delay_ms 150 --duration 8` and `python3 run.py --profile profiles/B.json --delay_ms 160 --duration 12`.
