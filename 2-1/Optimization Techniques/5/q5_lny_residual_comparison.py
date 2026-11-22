"""
Q5 - Residual Comparison: Original y vs ln(y) Polynomial Models (Degrees 1–8)
Fit polynomial models on both the original y and the log-transformed ln(y),
then plot the residuals (back-transformed to original y scale) for all degrees.
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load training data
train_df = pd.read_csv("egitim.csv")

X_train = train_df["x"].to_numpy()
y_train = train_df["y"].to_numpy()
y_train_ln = np.log(y_train)

# Compute residuals for both models across degrees 1–8
results = []

for degree in range(1, 9):
    X_mat = np.column_stack([X_train ** p for p in range(degree + 1)])
    XT    = X_mat.T

    # --- Original y model ---
    beta    = np.linalg.inv(XT @ X_mat) @ XT @ y_train
    y_pred  = X_mat @ beta

    # --- ln(y) model (predictions back-transformed) ---
    beta_ln    = np.linalg.inv(XT @ X_mat) @ XT @ y_train_ln
    y_pred_ln  = np.exp(X_mat @ beta_ln)

    for i in range(len(X_train)):
        results.append({
            "Degree":       degree,
            "X":            X_train[i],
            "Residual":     y_train[i] - y_pred[i],
            "Residual_ln":  y_train[i] - y_pred_ln[i],
        })

results_df = pd.DataFrame(results)
print(results_df)

# Plot
colors = ["red", "blue", "green", "gold", "purple", "orange", "pink", "cyan"]

residual_arr = results_df["Residual"].to_numpy()

plt.figure(figsize=(12, 7), dpi=120)

for degree in range(1, 9):
    data  = results_df[results_df["Degree"] == degree]
    color = colors[degree - 1]

    plt.plot(data["X"], data["Residual"],    color=color, marker="o", alpha=0.7,
             label=f"Original y – Degree {degree}")
    plt.plot(data["X"], data["Residual_ln"], color=color, marker="x", alpha=0.7,
             linestyle="--", label=f"ln(y) – Degree {degree}")

# Zero-residual reference line
plt.axhline(y=0, color="black", linestyle="--", linewidth=1)

plt.xlabel("X")
plt.ylabel("Residual (y − ŷ)")
plt.title("Q5 – Residuals: Original y vs ln(y) Models (Degrees 1–8)")

plt.xlim(X_train.min(), X_train.max())
plt.xticks(np.arange(np.floor(X_train.min()), np.ceil(X_train.max()) + 1, 0.5))

plt.ylim(residual_arr.min(), residual_arr.max())
plt.yticks(np.arange(np.floor(residual_arr.min()), np.ceil(residual_arr.max()) + 1, 0.15))

plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()

plt.savefig("q5_lny_residual_comparison.png", dpi=300, bbox_inches="tight")
plt.show()

