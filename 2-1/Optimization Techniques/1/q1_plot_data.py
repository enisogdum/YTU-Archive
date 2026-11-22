"""
Q1 - Visualize Training and Test Datasets
Plot training (egitim.csv) and test (test.csv) data on the same scatter plot.
"""

import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Load datasets
train_df = pd.read_csv("egitim.csv")
test_df = pd.read_csv("test.csv")

# Print basic info
print("=== Training Data ===")
print(f"Shape: {train_df.shape}")
print(train_df.describe())

print("\n=== Test Data ===")
print(f"Shape: {test_df.shape}")
print(test_df.describe())

# Plot
plt.figure(figsize=(8, 5))

plt.scatter(train_df["x"], train_df["y"], alpha=0.5, marker="o", label="Training", color="blue")
plt.scatter(test_df["x"],  test_df["y"],  alpha=0.5, marker="x", label="Test",     color="red")

plt.xlabel("X")
plt.ylabel("Y")
plt.title("Q1 – Training and Test Datasets")
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()

plt.savefig("q1_training_vs_test.png", dpi=300, bbox_inches="tight")
plt.show()
