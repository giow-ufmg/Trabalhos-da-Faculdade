# Calibrated-Game-Recommender-
Calibrated Steam Game Recommender based on RecSys Paper "Calibrated Recommenders" by Harald Steck

## Dependencies
To run this project you will need:
```
 - Numpy
 - Matplotlib
 - Pandas
 - Implicit
```
## Treat data
Everything related to treat the data is on clean_data folder, you can use your own, or our small preprocessed dataset
To use a larger dataset, put all json files from jmcauley steam dataset on the folder "data" and run "steam_games.py" and "user_item_playtime.py"

## How to run
```
python3 recommender.py
```

## How to use
You can change user, tweak settings using variables on code header

## References:
Calibrated Recommendations Paper from Harald Stack:
[paper](https://dl.acm.org/citation.cfm?id=3240372)

Calibrated Recommendations Presentations:
[presentation](https://www.youtube.com/watch?v=AlsPvceHVj4)

Steam dataset by Julian McAuley from University of California San Diego:  
[dataset](https://cseweb.ucsd.edu/~jmcauley/datasets.html#steam_data)

