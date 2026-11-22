# Numerical Analysis – Term Project (2026)

**Topic:** Ten numerical methods in one menu-driven C program, with functions typed in by the user and parsed at runtime
**Deadline:** 1 June 2026, 23:59 — online.yildiz.edu.tr (zip/rar only, no email)
**Check:** 2 June 2026, during class (online)
**Language:** C only

---

## Files

| File | Contents |
|---|---|
| `definiton.pdf` | Assignment description (requirements, rules, deliverables) |
| `23011056/23011056.c` | The whole program, one source file (~1,630 lines) |
| `23011056/report.pdf` | Report showing each method running (16 pages) |
| `23011056/~$011056.docx` | Word lock file left behind; not a real document, delete before zipping |

---

## Methods

| No | Method | Requirement | Function input | Code |
|---:|---|---|:---:|---|
| 1 | Bisection | | ✓ | `bisection_method()` |
| 2 | Regula-Falsi | | ✓ | `regula_falsi_method()` |
| 3 | Newton-Raphson | | ✓ | `newton_raphson_method()` |
| 4 | Inverse of an NxN matrix | N must be dynamic, not a small fixed size | | `inverse_matrix()` |
| 5 | Cholesky (ALU) | | | `cholesky_method()` |
| 6 | Gauss-Seidel | | | `gauss_seidel_method()` |
| 7 | Numerical derivative | Print forward, backward **and** central differences, no choice | ✓ | `derivative()` |
| 8 | Simpson | Print 1/3 **and** 3/8, no choice | ✓ | `simpson_method()` |
| 9 | Trapezoid | N comes from the user | ✓ | `trapez_method()` |
| 10 | Gregory-Newton interpolation (no variable transform) | | | `gregory_newton_method()` |

For methods 1, 2, 3, 7, 8 and 9 the user must type the function on the keyboard. It can combine polynomial, exponential, trigonometric, logarithmic and inverse trigonometric parts. **Hard-coded functions get no credit.** `^` is power and `_` is the log base. Examples from the assignment:

| Input | Meaning |
|---|---|
| `sin(x*e^(5x))` | sin(x · e^(5x)) |
| `x^(sin(log_5 (x^3)))` | x^sin(log₅(x³)) |
| `log_x(sin((5*x)^2 + sin(5*x)))` | log base x of sin((5x)² + sin(5x)) |

### Coding Rules

- C only, all 10 methods in **one** `.c` file.
- No `break` (except in `switch`), `continue` or `goto`.
- Modular code; a program written entirely in `main` is rejected.
- Must use dynamic memory (`malloc` etc.) and `struct`s.

### Deliverables (`23011056.zip`)

- [x] Source code — `23011056.c`
- [x] Report — currently `report.pdf`; must be named **`23011056.pdf`**
- [ ] Zip both into `23011056.zip` and upload; save a screenshot of the successful upload as proof

---

## How the Program Works

Build and run:

```bash
cc -Wall -o numeric 23011056/23011056.c -lm
```

```bash
./numeric
```

The menu (in Turkish) lists options 0–10. After one method runs, the program exits.

**Expression parser.** The typed function goes through `tokenize()` → a recursive-descent parser (`parse_expression` / `parse_term` / `parse_factor` / `parse_primary`) → an expression tree of `Node` structs → `evaluate()`.

- Operators: `+ - * / ^`, parentheses
- Functions: `sin cos tan arcsin arccos arctan arccot sqrt abs exp ln log`
- Constants: `e`, `pi`
- Log with a base is written as **`log(base, arg)`**; `log(arg)` is the natural log.

**Rule check:** `break` appears only inside the `switch` in `main`; there is no `continue` or `goto`. Memory uses `malloc`/`calloc`, and the code uses `Token`, `Node` and `Variable` structs.

The code compiles with clang and shows 15 warnings, all for unused variables.

---

## Things to Fix Before Submitting

Tested by running option 7 (derivative) at x = 1 with the assignment's example inputs:

| Input | Result |
|---|---|
| `sin(x*e^(5*x))` | Works |
| `x^(sin(log(5,x^3)))` | Works |
| `sin(x*e^(5x))` | **Wrong value, no error.** `5x` is not read as `5*x`, so the result differs from the `5*x` version |
| `x^(sin(log_5 (x^3)))` | **Fails** (prints `nan`) |

- **Spaces cut the input off.** The function is read with `scanf("%s", ...)`, which stops at the first space. `log_5 (x^3)` and `(5*x)^2 + sin(5*x)` are both cut short. Read the whole line with `fgets` (or `scanf(" %255[^\n]", ...)`).
- **`_` log-base syntax is not supported.** The tokenizer skips `_`, so `log_5(x^3)` and `log_x(...)` don't parse. The assignment uses this syntax in all its log examples. Add a case that turns `log_<base>(<arg>)` into the existing two-argument log node.
- **No implicit multiplication.** `5x` should mean `5*x`. Insert a `*` token when a number is followed directly by a variable, function or `(`.
- **Rounded constants.** `pi` returns `3.14`, and `e` / `exp` / `ln` use `2.71828`. Use `M_PI`, `M_E`, `exp()` and `log()` from `math.h`.
- **`ln` with two arguments** ignores its base and always divides by ln(2.71828).
- **Variables other than `x`** are silently set to 1. Reject them with an error instead.
- **File names:** rename `report.pdf` to `23011056.pdf` and remove the `~$011056.docx` lock file before zipping.
- **Possibly an older version:** `23011056.c` was last changed on 16 May 2025, before this year's assignment. Check it against the 2026 requirements above (especially the dynamic-N matrix inverse and the "no choice" output for methods 7 and 8).
- **Report:** not checked here (the PDF is mostly images). Make sure it shows each method running, including at least one example of each function type.
