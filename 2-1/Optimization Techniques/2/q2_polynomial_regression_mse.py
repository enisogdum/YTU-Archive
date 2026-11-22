"""
Q2 - Polynomial Regression: Train vs Test MSE (Degrees 1–8)
Fit polynomial models of degree 1 through 8 using the analytical (normal-equation)
solution and compare Train MSE vs Test MSE.
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load datasets
train_df = pd.read_csv("egitim.csv")
test_df  = pd.read_csv("test.csv")

X_train = train_df["x"].to_numpy()
y_train = train_df["y"].to_numpy()

X_test  = test_df["x"].to_numpy()
y_test  = test_df["y"].to_numpy()

# Fit polynomial models for degrees 1 to 8
results = []

for degree in range(1, 9):
    # Build Vandermonde-style feature matrices
    X_train_mat = np.column_stack([X_train ** p for p in range(degree + 1)])
    X_test_mat  = np.column_stack([X_test  ** p for p in range(degree + 1)])

    # Analytical (normal equation) solution: β = (XᵀX)⁻¹ Xᵀ y
    XT   = X_train_mat.T
    beta = np.linalg.inv(XT @ X_train_mat) @ XT @ y_train

    # Predictions
    y_train_pred = X_train_mat @ beta
    y_test_pred  = X_test_mat  @ beta

    # MSE
    train_mse = np.mean((y_train - y_train_pred) ** 2)
    test_mse  = np.mean((y_test  - y_test_pred)  ** 2)

    results.append({"Degree": degree, "Train MSE": train_mse, "Test MSE": test_mse})

results_df = pd.DataFrame(results)

print("=== Polynomial Regression MSE ===")
print(results_df.to_string(index=False))

# Plot Train MSE vs Test MSE
plt.figure(figsize=(10, 6))

plt.plot(results_df["Degree"], results_df["Train MSE"], marker="o", label="Train MSE")
plt.plot(results_df["Degree"], results_df["Test MSE"],  marker="s", label="Test MSE")

plt.xlabel("Polynomial Degree")
plt.ylabel("Mean Squared Error (MSE)")
plt.title("Q2 – Train vs Test MSE for Polynomial Regression (Degrees 1–8)")
plt.xticks(range(1, 9))
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig("q2_polynomial_regression_mse.png", dpi=300, bbox_inches="tight")
plt.show()

