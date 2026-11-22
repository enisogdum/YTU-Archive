"""
Q7 - Gradient Descent: Loss Convergence for y and ln(y) Models
Train degree-3 polynomial models for both y and ln(y) using gradient descent
and plot the loss curve over iterations to compare convergence.
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load training data
train_df = pd.read_csv("egitim.csv")

X_train    = train_df["x"].to_numpy()
y_train    = train_df["y"].to_numpy()
y_train_ln = np.log(y_train)

# Hyperparameters
degree_y  = 3
degree_ln = 3
lr        = 0.0001   # learning rate (epsilon)
n_iters   = 50000

# --- Original y model (gradient descent) ---
X_mat_y = np.column_stack([X_train ** p for p in range(degree_y + 1)])
XT_y    = X_mat_y.T
beta_y  = np.zeros(X_mat_y.shape[1])

loss_y = []
for _ in range(n_iters):
    y_pred  = X_mat_y @ beta_y
    beta_y  = beta_y - lr * (XT_y @ (y_pred - y_train)) / len(y_train)
    loss_y.append(np.sum((y_pred - y_train) ** 2))

# --- ln(y) model (gradient descent) ---
X_mat_ln = np.column_stack([X_train ** p for p in range(degree_ln + 1)])
XT_ln    = X_mat_ln.T
beta_ln  = np.zeros(X_mat_ln.shape[1])

loss_ln = []
for _ in range(n_iters):
    y_pred_ln = X_mat_ln @ beta_ln
    beta_ln   = beta_ln - lr * (XT_ln @ (y_pred_ln - y_train_ln)) / len(y_train_ln)
    loss_ln.append(np.sum((np.exp(y_pred_ln) - y_train) ** 2))

print("=== Gradient Descent Results ===")
print(f"Coefficients [y model]:     {beta_y}")
print(f"Coefficients [ln(y) model]: {beta_ln}")
print(f"Final Loss [y]:    {loss_y[-1]:.6f}")
print(f"Final Loss [ln(y)]: {loss_ln[-1]:.6f}")

# Plot loss curves
plt.figure(figsize=(12, 7), dpi=120)

plt.plot(range(n_iters), loss_y,  label=f"y model – Degree {degree_y}")
plt.plot(range(n_iters), loss_ln, linestyle="--", label=f"ln(y) model – Degree {degree_ln}")

plt.xlabel("Iteration")
plt.ylabel("Loss (SSE)")
plt.title("Q7 – Gradient Descent Loss: y vs ln(y) Models")

plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()

plt.savefig("q7_gradient_descent_loss.png", dpi=300, bbox_inches="tight")
plt.show()

