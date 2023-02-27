import optuna

storage_name = "ahcxxx.db"
study_name = "study_name"

study = optuna.load_study(
    storage=f"sqlite:///{storage_name}",
    study_name=study_name
)

print(f"{study.best_trial=}")
print(f"{study.best_value=}")
print(f"{study.best_params=}")

# visualizeは $ optuna-dashboard sqlite:///{storage_name}.db で可能
# https://optuna.readthedocs.io/en/stable/tutorial/10_key_features/005_visualization.html
