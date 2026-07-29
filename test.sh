#!/usr/bin/env bash
# Run all local checks for this assignment.

set -euo pipefail

make clean
make

echo "Running profile A at 150 ms..."
python3 run.py --profile profiles/A.json --delay_ms 150

echo "Running profile B at 160 ms..."
python3 run.py --profile profiles/B.json --delay_ms 160
