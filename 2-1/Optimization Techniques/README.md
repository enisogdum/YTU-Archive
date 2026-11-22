# BLM2642 – Homework 1: Polynomial Regression

**Topic:** Polynomial regression with the closed-form solution, the ln(y) transform, and gradient descent
**Language:** Python

---

## Data Files

| File | Contents |
|---|---|
| `egitim.csv` | Training set: 50 points (x, y); x ∈ [−3, 0.5] ∪ [1.5, 3] |
| `test.csv` | Test set: 20 points (x, y) from the same ranges |
| `tahmin_x.csv` | 30 points from [−4, 4]; only `id, x` are given |

The data comes from an unknown function with added noise. All y values are positive.
There is no training data in [0.5, 1.5] (the interpolation gap).

---

## Tasks

1. Plot the training and test data on the same chart.
2. For every degree from 1 to 8, solve polynomial regression with the normal equation **β = (XᵀX)⁻¹Xᵀy** (build the X matrix yourself). Show training and test MSE in a table and on one chart.
3. Choose a degree and justify the choice.
4. Plot the residuals (actual − predicted) of the chosen model against x. Compare them with the residuals of the models one degree lower and one degree higher.
5. Repeat the analysis on **ln(y)**: fit on ln(y), convert predictions back with `exp`, and compute the errors on the original y scale. Compare the two approaches and explain why the transform did or didn't help.
6. Plot the chosen y and ln(y) models over [−4, 4] together with the training data. Compare them in the interpolation region [0.5, 1.5] and the extrapolation regions [−4, −3] and [3, 4].
7. Train the chosen models with **gradient descent**. Plot the loss curve and compare the coefficients with the closed-form solution.
8. Predict the 30 points in `tahmin_x.csv` with the best model and submit them as `studentNo_tahmin.csv` (columns `id, y`). Predictions are graded against the true values.


---

## Summary of Results (from `report.pdf`)

### 2. MSE by Degree (fitted on y, closed-form solution)

| Degree | Train MSE | Test MSE |
|---:|---:|---:|
| 1 | 0.2170 | 0.1465 |
| 2 | 0.2166 | 0.1404 |
| 3 | 0.0448 | 0.0498 |
| 4 | 0.0290 | 0.0513 |
| 5 | 0.0251 | 0.0458 |
| 6 | 0.0231 | 0.0467 |
| 7 | 0.0230 | 0.0479 |
| 8 | 0.0220 | 0.0540 |

### 3. Degree Choice
Degrees 1–2 underfit. Error drops sharply at degree 3. Beyond degree 4 the gain is very small, and test error rises again at degree 8. **Chosen: degree 4.**

### 4. Residual Analysis (degrees 3, 4, 5)
- Degree 3: large residuals near x ≈ −3 (≈ −0.54) and x ≈ 0.2 (≈ −0.41), plus a systematic pattern, so it misses the curvature.
- Degrees 4 and 5: residuals stay in a narrow band around zero and are nearly identical.
- The large swings for x > 1.5 appear in every model, so they come from noise rather than the model.

### 5. ln(y) Transform
- Models fitted on ln(y) fit much better, especially at low degrees; a degree-2 ln(y) model matches a degree-4 y model.
- The exception is degree 1, which is a pure exponential and cannot follow the shape of the data.
- Interpretation: the data looks like **y ≈ e^(a + bx + cx²)**. The log transform turns that curvature into a low-degree polynomial and guarantees positive predictions.

### 6. Interpolation and Extrapolation (degree-3 y model vs degree-3 ln(y) model)

| Region | y model | ln(y) model |
|---|---|---|
| Training data, low y (x ≈ −3 to −1) | Poor fit; predicts negative values near x ≈ −2.1 | Follows the points almost exactly |
| Interpolation [0.5, 1.5] | Smooth and increasing | Smooth and increasing (gap ≤ ~0.4) |
| Positive extrapolation [3, 4] | Drops to ≈ 2.1 at x = 4 | Drops to ≈ 2.1 at x = 4; neither is reliable |
| Negative extrapolation [−4, −3] | Turns upward (≈ 3.3 at x = −4), which is wrong | Stays near zero and positive, which matches the trend |

### 7. Gradient Descent (learning rate 0.0001, 50,000 iterations, β starts at 0)

| Coefficient | y – closed form | y – GD | ln(y) – closed form | ln(y) – GD |
|---|---:|---:|---:|---:|
| β₀ | 1.9861 | 1.4770 | 0.5298 | 0.3656 |
| β₁ | 1.5291 | 1.3020 | 0.9089 | 0.7986 |
| β₂ | 0.0443 | 0.1374 | −0.2038 | −0.1750 |
| β₃ | −0.1049 | −0.0752 | −0.0021 | 0.0135 |

- The y model's loss falls from ≈ 500 to ≈ 7. The ln(y) loss, measured on the y scale, is not monotonic: ≈ 300 → 125 → 390 → ≈ 8.
- Neither model fully converges. The small learning rate, unscaled columns (x³ reaches ±27) and the strong correlation between the 1 and x² columns slow it down.
- Fixes: run more iterations or scale the features.

### 8. Final Predictions
- **Model:** degree-3 ln(y), trained with gradient descent; ŷ = e^(p(x)).
- Reason: predictions are always positive and behave sensibly at the edges, especially in negative extrapolation.
- Caveat: because GD did not converge, predictions for x ≈ 1.5–2.3 are too low. β₃ has the opposite sign from the closed-form value, so the curve rises to ≈ 5.05 at x = 4 instead of falling to ≈ 2.1.

---

