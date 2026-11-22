"""
Q4 - Residual Plot: Polynomial Regression (Degrees 3, 4, 5)
Plot training residuals (y - ŷ) for polynomial models of degree 3, 4, and 5
to compare their fit on the training data.
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load training data
train_df = pd.read_csv("egitim.csv")

X_train = train_df["x"].to_numpy()
y_train = train_df["y"].to_numpy()

# Compute residuals for degrees 3, 4, 5
results = []

for degree in range(3, 6):
    X_mat = np.column_stack([X_train ** p for p in range(degree + 1)])

    # Normal equation
    XT   = X_mat.T
    beta = np.linalg.inv(XT @ X_mat) @ XT @ y_train
    y_pred = X_mat @ beta

    for i in range(len(X_train)):
        results.append({
            "Degree":   degree,
            "X":        X_train[i],
            "Residual": y_train[i] - y_pred[i],
        })

results_df = pd.DataFrame(results)

# Plot residuals
degree_styles = [
    (3, "o", "blue"),
    (4, "x", "red"),
    (5, "v", "green"),
]

plt.figure(figsize=(12, 7), dpi=120)

for degree, marker, color in degree_styles:
    data = results_df[results_df["Degree"] == degree]
    plt.plot(
        data["X"],
        data["Residual"],
        alpha=0.6,
        marker=marker,
        label=f"Degree {degree}",
        color=color,
    )

# Zero-residual reference line
plt.axhline(y=0, color="black", linestyle="--", linewidth=1)

plt.xlabel("X")
plt.ylabel("Residual (y − ŷ)")
plt.title("Q4 – Training Residuals for Polynomial Regression (Degrees 3–5)")

plt.xlim(X_train.min(), X_train.max())
plt.xticks(np.arange(np.floor(X_train.min()), np.ceil(X_train.max()) + 0.5, 0.5))

plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()

plt.savefig("q4_residual_comparison.png", dpi=300, bbox_inches="tight")
plt.show()

