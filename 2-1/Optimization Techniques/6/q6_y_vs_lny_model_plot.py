"""
Q6 - Model Comparison: y vs ln(y) with Interpolation / Extrapolation Regions
Fit degree-3 polynomial models for both y and ln(y) (analytical solution),
then plot the fitted curves over the training data along with shaded regions
for interpolation and extrapolation.
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load training data
train_df = pd.read_csv("egitim.csv")

X_train = train_df["x"].to_numpy()
y_train = train_df["y"].to_numpy()
y_train_ln = np.log(y_train)

# Selected degree for both models
degree_y  = 3
degree_ln = 3

# Dense x-axis for smooth curve
X_plot = np.linspace(-4, 4, 500)

# --- Original y model ---
X_mat_y = np.column_stack([X_train ** p for p in range(degree_y + 1)])
XT_y    = X_mat_y.T
beta_y  = np.linalg.inv(XT_y @ X_mat_y) @ XT_y @ y_train

X_plot_mat_y = np.column_stack([X_plot ** p for p in range(degree_y + 1)])
y_plot       = X_plot_mat_y @ beta_y

# --- ln(y) model ---
X_mat_ln  = np.column_stack([X_train ** p for p in range(degree_ln + 1)])
XT_ln     = X_mat_ln.T
beta_ln   = np.linalg.inv(XT_ln @ X_mat_ln) @ XT_ln @ y_train_ln

X_plot_mat_ln = np.column_stack([X_plot ** p for p in range(degree_ln + 1)])
y_plot_ln     = np.exp(X_plot_mat_ln @ beta_ln)

print("Coefficients [y model]:")
print(beta_y)
print("\nCoefficients [ln(y) model]:")
print(beta_ln)

# Plot
plt.figure(figsize=(12, 7), dpi=120)

plt.scatter(X_train, y_train, marker="o", color="black", label="Training Data")

plt.plot(X_plot, y_plot,    label=f"y model – Degree {degree_y}")
plt.plot(X_plot, y_plot_ln, linestyle="--", label=f"ln(y) model – Degree {degree_ln}")

# Shaded regions
plt.axvspan( 0.5,  1.5, alpha=0.1, color="green",  label="Interpolation [0.5, 1.5]")
plt.axvspan( 3.0,  4.0, alpha=0.1, color="red",    label="Positive Extrapolation [3, 4]")
plt.axvspan(-4.0, -3.0, alpha=0.1, color="orange", label="Negative Extrapolation [−4, −3]")

plt.xlabel("X")
plt.ylabel("Y")
plt.title("Q6 – y vs ln(y) Model Comparison (Interpolation & Extrapolation)")

plt.xlim(-4, 4)
plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()

plt.savefig("q6_y_vs_lny_model_plot.png", dpi=300, bbox_inches="tight")
plt.show()

