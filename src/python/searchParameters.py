# https://blog.knshnb.com/posts/ahc007-optuna/

import os
import optuna
import joblib
import subprocess


n_parallel = 50
n_files = 100
n_trials = 100
storage_name = "AHCxxx"
study_name = "study_name"
answer_file_name = "main"


def calc_score_each(seed, Ps):
    in_file = f"in/{seed:04}.txt"
    out_file = f"/dev/null"

    cmd = f"tools/target/release/tester ./src/cpp/{answer_file_name} " + \
        " ".join(map(str, Ps)) + f" < {in_file} > {out_file}"
    child = subprocess.Popen(cmd, shell=True,
                             stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    _, stderr = child.communicate()

    try:
        score = int(stderr.split()[-1])
    except ValueError:
        print(stderr, flush=True)
        score = -1

    print(f"seed{seed}:{score}", end=" ", flush=True)

    return score


def calc_scores(Ps):
    scores = joblib.Parallel(n_jobs=n_parallel)(
        joblib.delayed(calc_score_each)(i, Ps) for i in range(n_files)
    )
    return scores


def objective(trial):
    print("start")

    P01 = trial.suggest_int("P01", 0, 1)
    P02 = trial.suggest_float("P02", 0.0, 1.0)

    PARAMS = [P01, P02]

    print("params:", PARAMS, sep=" ")

    scores = calc_scores(PARAMS)

    scores = [score for score in scores if score != -1]

    print(f"success:{len(scores)}")

    return sum(scores)


if __name__ == "__main__":
    print("setup start")

    os.system(
        f"/usr/bin/g++-10 -fdiagnostics-color=always ./src/cpp/{answer_file_name}.cpp -o ./src/cpp/{answer_file_name} -std=c++17 -Wall -Wextra -O3")

    study = optuna.create_study(
        direction="minimize",
        storage=f"sqlite:///{storage_name}.db",
        study_name=study_name,
        load_if_exists=True,
    )

    print("setup done")

    study.optimize(objective, n_trials=n_trials)
