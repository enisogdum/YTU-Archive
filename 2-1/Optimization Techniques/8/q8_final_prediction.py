"""
Q8 - Final Predictions Using the ln(y) Gradient Descent Model (Degree 3)
Train the ln(y) degree-3 polynomial model with gradient descent on egitim.csv,
then predict y values for the x values in tahmin_x.csv and save the results.
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load datasets
train_df      = pd.read_csv("egitim.csv")
prediction_df = pd.read_csv("tahmin_x.csv")

X_train    = train_df["x"].to_numpy()
y_train    = train_df["y"].to_numpy()
y_train_ln = np.log(y_train)

X_pred = prediction_df["x"].to_numpy()

# Hyperparameters
degree_ln = 3
lr        = 0.0001   # learning rate (epsilon)
n_iters   = 50000

# --- ln(y) model: gradient descent ---
X_mat_ln = np.column_stack([X_train ** p for p in range(degree_ln + 1)])
XT_ln    = X_mat_ln.T
beta_ln  = np.zeros(X_mat_ln.shape[1])

for _ in range(n_iters):
    y_pred_ln = X_mat_ln @ beta_ln
    beta_ln   = beta_ln - lr * (XT_ln @ (y_pred_ln - y_train_ln)) / len(y_train_ln)

# Predict on tahmin_x values
X_pred_mat  = np.column_stack([X_pred ** p for p in range(degree_ln + 1)])
y_predicted = np.exp(X_pred_mat @ beta_ln)

# Print and save predictions
print("=== Predictions ===")
print(np.column_stack((X_pred, y_predicted)))

pred_out = pd.DataFrame({"x": X_pred, "y_predicted": y_predicted})
pred_out.to_csv("23011056_tahmin.csv", index=False)
print("\nPredictions saved to 23011056_tahmin.csv")

# Plot: training data + prediction curve
order = np.argsort(X_pred)

plt.figure(figsize=(12, 7), dpi=120)

plt.scatter(X_train, y_train, s=10, alpha=0.5, label="Training Data")
plt.plot(
    X_pred[order],
    y_predicted[order],
    linestyle="-",
    label=f"ln(y) Model Prediction – Degree {degree_ln}",
)

plt.xlim(X_pred.min(), X_pred.max())
plt.xticks(np.arange(np.floor(X_pred.min()), np.ceil(X_pred.max()) + 0.5, 0.5))

plt.xlabel("X")
plt.ylabel("Y")
plt.title("Q8 – Final Predictions (ln(y) Gradient Descent Model)")

plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()

plt.savefig("q8_final_prediction.png", dpi=300, bbox_inches="tight")
plt.show()

