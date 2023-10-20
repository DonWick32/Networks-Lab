grep " 0 2 tcp " out.tr > output
grep "^r" out.tr > output
grep "^r" trace-file | grep " 0 2 tcp " > output   