#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Token types
typedef enum { FUNC, VAR, NUM, OP, PAR, COMMA} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[32];
} Token;

// Expression tree node structure
typedef struct Node {
    TokenType type;
    char value[32];
    struct Node* left;
    struct Node* right;
} Node;

typedef struct {
    char name[32];
    double value;
} Variable;

// TREE
int is_letter(char c); 
int is_digit(char c);
int is_operator(char c);
int get_precedence(char op);
const char* get_type_name(TokenType t);
int is_function(const char* str);
void tokenize(const char* expr, Token *tokens, int* token_count);
Node* create_node(TokenType type, const char* value);
Node* parse_expression(Token *tokens, int* index, int token_count);
Node* parse_term(Token *tokens, int* index, int token_count);
Node* parse_factor(Token *tokens, int* index, int token_count);
Node* parse_primary(Token *tokens, int* index, int token_count);
double evaluate(Node* root, double *x_value, int *x_asked);
void free_tree(Node* root);

// NEEDED FUNCTİON
void free_memory(double **coef_matrix, double *constants, double *x, double *x_prev, int n);

//FUNCTİON
void bisection_method();
void regula_falsi_method();
void newton_raphson_method();
void inverse_matrix();
void cholesky_method();
void gauss_seidel_method();
void derivative();
void simpson_method();
void simpson_method();
void trapez_method();
void gregory_newton_method();

int main() {
    int choice;
    int game_running;

game_running=1;
while (game_running)
{
    printf("Hangi sayısal analiz türünü seçmek istersiniz?\n");
    printf("0. Çıkış\n1. Bisection Yöntemi\n2. Regula-Falsi Yöntemi\n3. Newton-Raphson Yöntemi\n4. NxN'lik bir matrisin tersi\n5. Cholesky (ALU ) Yöntemi\n6. Gauss Seidal Yöntemi\n7. Sayisal Türev (merkezi, ileri ve geri farklar tümü hesaplanmalidir)\n8. Simpson Yöntemi(hem 1/3, hem de 3/8 hesaplamali)\n9. Trapez Yöntemi\n10. Degisken dönüsümsüz Gregory Newton Enterpolasyonu\n");
    scanf("%d",&choice);
    switch (choice)
{
case 0:
      game_running=0;
      break;
case 1:
    bisection_method();
    game_running=0;
    break;
case 2:
     regula_falsi_method();
     game_running=0;
    break;
case 3:
     newton_raphson_method();
     game_running=0;
      break;

case 4:
    inverse_matrix();
    game_running=0;
    break;

case 5:
     cholesky_method();
     game_running=0;
     break;

case 6:
     gauss_seidel_method();
     game_running=0;
     break;

case 7:
     derivative();
     game_running=0;
     break;
    
case 8:
     simpson_method();
     game_running=0;
     break;

case 9:
       trapez_method();
       game_running=0;
      break;

case 10:
    gregory_newton_method();
    game_running=0;
     break;
    
default:
    printf("0 ve 10 arasında seçim yapınız!!\n");
    break;
}

}

    return 0;
}

int is_letter(char c) {
    return (c >= 'a' && c <= 'z');
}

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int get_precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

const char* get_type_name(TokenType t) {
    switch(t) {
        case FUNC: return "FUNC";
        case VAR: return "VAR";
        case NUM: return "NUM";
        case OP: return "OP";
        case PAR: return "PAR";
        case COMMA: return "COMMA";
        default: return "UNKNOWN";
    }
}

int is_function(const char* str) {

    int i;
    const char* functions[] = {"log", "sin", "cos", "tan", "sqrt", "abs", "arcsin", "arccos", "arctan", "arccot","","pi","e","ln","exp",NULL};
    for (i = 0; functions[i] != NULL; i++) {
        if (strcmp(str, functions[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void tokenize(const char* expr, Token *tokens, int* token_count) {
    int i;
    int j;
    int len = strlen(expr);
    int token_index = 0;
    char *buffer;

    for (i = 0; i < len;) {
         // boşluk varsa düz ilerle
        if (expr[i] == ' ') {
            i++; 
        } else if (is_letter(expr[i])) {
            // buffer tek tek tokenleri tutan değişken
            buffer = (char*)calloc(32, sizeof(char));
            j = 0;
            while (i < len && (is_letter(expr[i]) || is_digit(expr[i]))) {
                buffer[j++] = expr[i++];
            }
            buffer[j] = '\0';
            if (is_function(buffer) == 1) {
                tokens[token_index].type = FUNC;
            } else {
                tokens[token_index].type = VAR;
            }
            strcpy(tokens[token_index++].value, buffer);
            free(buffer);
        } else if (is_digit(expr[i])) {
            buffer = (char*)calloc(32, sizeof(char));
            j = 0;
            while (i < len && (is_digit(expr[i]) || expr[i] == '.')) {
                buffer[j++] = expr[i++];
            }
            buffer[j] = '\0';
            tokens[token_index].type = NUM;
            strcpy(tokens[token_index++].value, buffer);
            free(buffer);
        } else if (is_operator(expr[i])) {
            tokens[token_index].type = OP;
            tokens[token_index].value[0] = expr[i];
            tokens[token_index].value[1] = '\0';
            token_index++;
            i++;
        } else if (expr[i] == '(' || expr[i] == ')') {
            tokens[token_index].type = PAR;
            tokens[token_index].value[0] = expr[i];
            tokens[token_index].value[1] = '\0';
            token_index++; 
            i++;
        } else if (expr[i] == ',') {
            tokens[token_index].type = COMMA;
            tokens[token_index].value[0] = ',';
            tokens[token_index].value[1] = '\0';
            token_index++;
            i++;
        } else {
            i++; // Tanınmayan karakterleri atla
        }
    }
    *token_count = token_index;
}

Node* parse_primary(Token *tokens, int* index, int token_count) {
    Node* root = NULL;

    if (*index >= token_count) {
        return NULL;
    }

    if (tokens[*index].type == FUNC) {
        root = create_node(FUNC, tokens[*index].value);
        (*index)++;

        if (*index < token_count && tokens[*index].type == PAR && tokens[*index].value[0] == '(') {
            (*index)++;
            root->left = parse_expression(tokens, index, token_count);

            if (*index < token_count && tokens[*index].type == COMMA) {
                (*index)++;
                root->right = parse_expression(tokens, index, token_count);
            }

            if (*index < token_count && tokens[*index].type == PAR && tokens[*index].value[0] == ')') {
                (*index)++;
            } else {
                printf("eksik parantez!\n");
            }
        } else {
            printf("parantez hatası!\n");
        }
    } else if (tokens[*index].type == NUM) {
        root = create_node(tokens[*index].type, tokens[*index].value);
        (*index)++;
    } else if (tokens[*index].type == VAR) {
        root = create_node(tokens[*index].type, tokens[*index].value);
        (*index)++;
    } else if (tokens[*index].type == PAR && tokens[*index].value[0] == '(') {
        (*index)++;
        root = parse_expression(tokens, index, token_count);
        if (*index < token_count && tokens[*index].type == PAR && tokens[*index].value[0] == ')') {
            (*index)++;
        } else {
            printf("eksik parantez\n");
        }
    } else {
        printf("tanımlanmamış token: %s\n", tokens[*index].value);
    }

    return root;
}

Node* create_node(TokenType type, const char* value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("memory de yer ayrılamadı!\n");
        exit(1);
    }
    new_node->type = type;
    strcpy(new_node->value, value);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node* parse_factor(Token *tokens, int* index, int token_count) {
    Node* factor;
    Node* neg;
    Node* mult;
    char op;
    
    if (*index < token_count && tokens[*index].type == OP && 
        (tokens[*index].value[0] == '+' || tokens[*index].value[0] == '-')) {
        op = tokens[*index].value[0];
        (*index)++;
        
        factor = parse_factor(tokens, index, token_count);
        
        if (op == '-') {

            neg = create_node(NUM, "-1");
            mult = create_node(OP, "*");
            mult->left = neg;
            mult->right = factor;
            return mult;
        }
        return factor;
    }
    
    return parse_primary(tokens, index, token_count);
}

Node* parse_term(Token *tokens, int* index, int token_count) {
    Node* left = parse_factor(tokens, index, token_count);
    Node* op_node;
    
    while (*index < token_count && tokens[*index].type == OP && 
           (tokens[*index].value[0] == '*' || tokens[*index].value[0] == '/' || tokens[*index].value[0] == '^')) {
        op_node = create_node(OP, tokens[*index].value);
        (*index)++;
        
        op_node->left = left;
        op_node->right = parse_factor(tokens, index, token_count);
        left = op_node;
    }
    
    return left;
}

Node* parse_expression(Token *tokens, int* index, int token_count) {
    Node* left = parse_term(tokens, index, token_count);
    Node* op_node;
    
    while (*index < token_count && tokens[*index].type == OP && 
           (tokens[*index].value[0] == '+' || tokens[*index].value[0] == '-')) {
        op_node = create_node(OP, tokens[*index].value);
        (*index)++;
        
        op_node->left = left;
        op_node->right = parse_term(tokens, index, token_count);
        left = op_node;
    }
    
    return left;
}

double evaluate(Node* root, double *x_value, int *x_asked) {
    double left_value;
    double right_value;
    
    if (root == NULL) return 0;

    if (root->type == NUM) {
        return atof(root->value);
    } else if (root->type == VAR) {
        if (strcmp(root->value, "x") == 0) {
            if (*x_asked == 0) {
                printf("x değerini gir: ");
                scanf("%lf", x_value);
                *x_asked = 1;
            }
            return *x_value;
        } else {
            printf("%s x dışında variable 1 olarak atandı\n", root->value);
            return 1; 
        }
    } else if (root->type == FUNC) {
        left_value = evaluate(root->left, x_value, x_asked);
        right_value = root->right ? evaluate(root->right, x_value, x_asked) : 0;

        if (strcmp(root->value, "log") == 0) {
            if (root->right) {
                // Taban>left_value ve denklem>right_value
                if (left_value <= 0 || left_value == 1 || right_value <= 0) {
                    printf("geçersiz logaritma\n");
                    return NAN;
                }
                return log(right_value) / log(left_value);
            } else {
                // Natural logarithm
                if (left_value <= 0) {
                    printf("taban negatif olamaz\n");
                    return NAN;
                }
                return log(left_value);
            }
        }
        if (strcmp(root->value, "ln") == 0) {
            if (root->right) {
                // Base is left_value and argument is right_value
                if (left_value <= 0 || left_value == 1 || right_value <= 0) {
                    printf("geçersiz ln girişi\n");
                    return NAN;
                }
                return log(right_value) / log(2.71828);
            } else {
                // Natural logarithm
                if (left_value <= 0) {
                    printf("taban negatif olamaz\n");
                    return NAN;
                }
                return log(left_value);
            }
        }
        
        if (strcmp(root->value, "sin") == 0) return sin(left_value);
        if (strcmp(root->value, "cos") == 0) return cos(left_value);
        if (strcmp(root->value, "tan") == 0) return tan(left_value);
        if (strcmp(root->value, "arcsin") == 0) return asin(left_value);
        if (strcmp(root->value, "arccos") == 0) return acos(left_value);
        if (strcmp(root->value, "arctan") == 0) return atan(left_value);
        if (strcmp(root->value, "arccot") == 0) return atan(1/left_value);
        if (strcmp(root->value, "exp") == 0) return pow(2.71828, left_value);
        if (strcmp(root->value, "pi") == 0) return 3.14;
        if (strcmp(root->value, "e") == 0) return 2.71828;
        if (strcmp(root->value, "sqrt") == 0) {
            if (left_value < 0) {
                printf("negatif sayıların kökü yoktur!\n");
                return NAN;
            }
            return sqrt(left_value);
        }
        if (strcmp(root->value, "abs") == 0) return fabs(left_value);
    } else if (root->type == OP) {
        left_value = evaluate(root->left, x_value, x_asked);
        right_value = evaluate(root->right, x_value, x_asked);

        if (root->value[0] == '+') return left_value + right_value;
        if (root->value[0] == '-') return left_value - right_value;
        if (root->value[0] == '*') return left_value * right_value;
        if (root->value[0] == '/') {
            if (right_value == 0) {
                printf("sıfır paydada bulunamaz\n");
                return INFINITY;
            }
            return left_value / right_value;
        }
        if (root->value[0] == '^') return pow(left_value, right_value);
    }
    return 0;
}

void free_memory(double **coef_matrix, double *constants, double *x, double *x_prev, int n) {
    for (int i = 0; i < n; i++) {
        free(coef_matrix[i]);
    }
    free(coef_matrix);
    free(constants);
    free(x);
    free(x_prev);
}

void free_tree(Node* root) {
    if (root == NULL) return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void bisection_method() {

// tokenizer için declaration
    char *temp;
    char *input;
    int index;
    int token_count = 0;
    Node* root;
    double x_value = 0.0;
    int x_asked = 0;

// bisection için declaration
    double start, end, epsilon;
    int control=1;
    double control1,control2;
    double mid, f_start, f_end, f_mid;
    int iteration = 0;

    // fonksiyonu kullanıcıdan al
    temp = (char*)calloc(256, sizeof(char));
    printf("Matematiksel ifadeyi girin: ");
    scanf("%s", temp);
    input = (char*)calloc((strlen(temp)+1), sizeof(char));
    strcpy(input, temp);
    free(temp);
    
    // Tokenlerine ayırıp parse et
    Token *tokens = (Token*)calloc(100, sizeof(Token));
    tokenize(input, tokens, &token_count);
    free(input);
    
    index = 0;
    root = parse_expression(tokens, &index, token_count);
    free(tokens);
    
    if (root == NULL) {
        printf("İfade ayrıştırılamadı\n");
        return;
    }
    

    // giriş değerlerini kullanıcıdan al

    printf("Başlangıç: ");
    scanf("%lf", &start);
    printf("Bitiş: ");
    scanf("%lf", &end);
    printf("Epsilon: ");
    scanf("%lf", &epsilon);
    
 // x verilmezse 1 den başlat
    x_asked = 1; 

    // hesaplamaya start değerinden başla
    x_value = start;
    f_start = evaluate(root, &x_value, &x_asked);
    
    // hesaplamayı end değeri ile bitir
    x_value = end;
    f_end = evaluate(root, &x_value, &x_asked);
    
    // kök kontrolü
    if (f_start * f_end >= 0) {
        printf("f(start) ve f(end) zıt işaretlere sahip olmalıdır.\n");
        printf("f(%.6f) = %.6f, f(%.6f) = %.6f\n", start, f_start, end, f_end);
        free_tree(root);
        return;
    }
    
    printf("start: %+f\n", start);
    printf("end: %+f\n", end);
    
    mid = (start + end) / 2.0;
    printf("mid: %+f\n", mid);
    
    x_value = start;
    f_start = evaluate(root, &x_value, &x_asked);
    printf("f(start): %+f\n", f_start);
    
    x_value = end;
    f_end = evaluate(root, &x_value, &x_asked);
    printf("f(end): %+f\n", f_end);
    
    x_value = mid;
    f_mid = evaluate(root, &x_value, &x_asked);
    printf("f(mid): %+f\n", f_mid);
    
    // uygun değer bulana kadar devam et
    while (control) {
        iteration++;
        
        // yeni kök değeri bulma
        mid = (start + end) / 2.0;
        control1=mid;

        
        // yeni sınırları bulma
        x_value = mid;
        f_mid = evaluate(root, &x_value, &x_asked);
        
        printf("iteration : %d\n", iteration);
        printf("start: %+f\n", start);
        printf("end: %+f\n", end);
        printf("mid: %+f\n", mid);
        printf("f(start): %+f\n", f_start);
        printf("f(end): %+f\n", f_end);
        printf("f(mid): %+f\n", f_mid);
        
        
        // sınırları uygun aralıklarla değiştirme 
        if (f_start * f_mid < 0) {
            end = mid;
            f_end = f_mid;
            control2=(start+end)/2;
        } else {
            start = mid;
            f_start = f_mid;
            control2=(start+end)/2;
        }
         // kök bulunursa fonksiyondan çıkma 
        if (fabs(f_mid) < epsilon || (end - start) < epsilon) {
             printf("Kök bulundu!\n");
                 printf("Sonuç: %.10f\n", mid);
                control=0;
            
        }
        printf("\n");
    }
    
 
    // memory serbest bırak
    free_tree(root);
}

void regula_falsi_method() {

    // tokenizer için declaration
    char *temp;
    char *input;
    int index;
    int token_count = 0;
    Node* root;
    double x_value = 0.0;
    int x_asked = 0;

    // regula-falsi için declaration
    double start, end, epsilon;
    double next, f_start, f_end, f_mid;
    int iteration = 0;
    int control=1;
 
    // ifadeyi kullanıcıdan alma
    temp = (char*)calloc(256, sizeof(char));
    printf("Matematiksel ifadeyi girin: ");
    scanf("%s", temp);
    input = (char*)calloc((strlen(temp)+1), sizeof(char));
    strcpy(input, temp);
    free(temp);
    
    // Tokenize etmek ve parse et
    Token *tokens = (Token*)calloc(100, sizeof(Token));
    tokenize(input, tokens, &token_count);
    free(input);
    
    index = 0;
    root = parse_expression(tokens, &index, token_count);
    free(tokens);
    
    if (root == NULL) {
        printf("İfade ayrıştırılamadı\n");
        return;
    }
    

    // Regula-falsi için başlangıç son ve epsilon değerlerini al
    printf("Başlangıç: ");
    scanf("%lf", &start);
    printf("Bitiş: ");
    scanf("%lf", &end);
    printf("Epsilon: ");
    scanf("%lf", &epsilon);
    
    
// x değeri belirlenmezse 1 den başlat
    x_asked = 1; 
    
    // başlangıç değerlerini hesapla
    x_value = start;
    f_start = evaluate(root, &x_value, &x_asked);
    
    // son değerini hesapla
    x_value = end;
    f_end = evaluate(root, &x_value, &x_asked);
    
    // kök var mı diye kontrol et
    if (f_start * f_end >= 0) {
        printf("f(start) ve f(end) zıt işaretlere sahip olmalıdır.\n");
        printf("f(%.6f) = %.6f, f(%.6f) = %.6f\n", start, f_start, end, f_end);
        free_tree(root);
        return;
    }
    
    printf("start: %+f\n", start);
    printf("end: %+f\n", end);
    

    // epsilon değerine yaklaşana kadar döngü

     while (control) {
        iteration++;
        
        // yeni kök değerini hesapla
        next = ((start * f_end)-(end * f_start))/ (f_end-f_start);
        
        // kökün fonksiyondaki değerini hesapla
        x_value = next;
        f_mid = evaluate(root, &x_value, &x_asked);
        
        printf("iteration : %d\n", iteration);
        printf("start: %+f\n", start);
        printf("end: %+f\n", end);
        printf("mid: %+f\n", next);
        printf("f(start): %+f\n", f_start);
        printf("f(end): %+f\n", f_end);
        printf("f(mid): %+f\n", f_mid);
        
        
        // uygun noktalarla değiştirme
        if (f_start * f_mid < 0) {
            end = next;
            f_end = f_mid;
        } else {
            start = next;
            f_start = f_mid;
        }
         // köke gereği kadar yaklaşırsan döngüden çık yaklaşmazsa kodu bitir
        if (fabs(f_mid) < epsilon || (end - start) < epsilon) {
             printf("Kök bulundu!\n");
                 printf("Sonuç: %.10f\n", next);
                control=0;
            
        }
        else if (iteration==20 && fabs(f_mid) > epsilon){
           printf("kök bulunamadı!\n");
           control=0;
        }
        
    }
    
 
    // memory serbest bırak
    free_tree(root);

}

void newton_raphson_method() {

    //  tokenizer için declaration
    char *temp, *input;
    int index, token_count = 0;
    Node* root;
    double x_value = 0.0, epsilon;
    int x_asked = 1;

    // newton raphson için declaration
    double derivative, value1, value2, f_value;
    int control = 1, iteration = 0;
    double next;


    // Kullanıcıdan ifade al
    temp = (char*)calloc(256, sizeof(char));
    printf("Matematiksel ifadeyi girin: ");
    scanf("%s", temp);
    input = (char*)calloc(strlen(temp) + 1, sizeof(char));
    strcpy(input, temp);
    free(temp);

    // Tokenize et ve parse et
    Token *tokens = (Token*)calloc(100, sizeof(Token));
    tokenize(input, tokens, &token_count);
    free(input);

    index = 0;
    root = parse_expression(tokens, &index, token_count);
    free(tokens);

    if (root == NULL) {
        printf("İfade ayrıştırılamadı\n");
        return;
    }


    // Başlangıç ve epsilon al
    printf("Başlangıç: ");
    scanf("%lf", &x_value);
    printf("Epsilon: ");
    scanf("%lf", &epsilon);

    while (control && iteration < 20) {
        iteration++;

        f_value = evaluate(root, &x_value, &x_asked);

        value1 = x_value + epsilon;
        value2 = x_value - epsilon;
        derivative = (evaluate(root, &value1, &x_asked) - evaluate(root, &value2, &x_asked)) / (2 * epsilon);

         next = x_value - (f_value / derivative);

        printf("iteration : %d\n", iteration);
        printf("xn: %+f\n", x_value);
        printf("xn+1: %+f\n", next);
        printf("f(xn): %+f\n", f_value);
        printf("f'(xn): %+f\n\n", derivative);

        // Kök kontrolü
        if (fabs(f_value) < epsilon || fabs(next - x_value) < epsilon) {
            printf("Kök bulundu!\nSonuç: %.10f\n", next);
            control = 0;
        }

        x_value = next;
    }

    // memory serbest bırak
    free_tree(root);
}

void inverse_matrix() {

    // matris için declarationlar
    double **matrix;
    double **unit_matrix;
    int n, m;
    int N;
    int i, j, k;
    double temp;


    // Kare matris kontrolü
    do {
        printf("Matris boyutlarını giriniz (örn: 3 3): ");
        scanf("%d %d", &n, &m);
        if (n != m) {
            printf("Boyutlar eşit değil! Ters matris sadece kare matrisler için hesaplanabilir.\n");
        }
    } while (n != m);
    N = n;

    // Bellek ayırma
    matrix = (double **)calloc(N, sizeof(double *));
    unit_matrix = (double **)calloc(N, sizeof(double *));
    for (i = 0; i < N; i++) {
        matrix[i] = (double *)calloc(N, sizeof(double));
        unit_matrix[i] = (double *)calloc(N, sizeof(double));
    }

    // Matris elemanlarını alma
    printf("Matris elemanlarını giriniz:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    // Birim matris oluşturma
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i == j)
                unit_matrix[i][j] = 1;
            else
                unit_matrix[i][j] = 0;
        }
    }

    // Gauss-Jordan Eliminasyonu
    for (i = 0; i < N; i++) {

        // Ana köşedeki elemanı 1 yap
        temp = matrix[i][i];
        if (temp == 0) {
            printf("Matris tekil, ters matris hesaplanamaz.\n");
            return;
        }
        // yapılan değşikler aynı anda birim matrisede geçmek zorunda
        for (j = 0; j < N; j++) {
            matrix[i][j] /= temp;
            unit_matrix[i][j] /= temp;
        }

        // Diğer satırlardaki o sütunu 0 yap
        for (k = 0; k < N; k++) {
            if (k != i) {
                temp = matrix[k][i];
                for (j = 0; j < N; j++) {
                    matrix[k][j] -= temp * matrix[i][j];
                    unit_matrix[k][j] -= temp * unit_matrix[i][j];
                }
            }
        }
    }

    // Sonuç: unit_matrix artık matrisin tersidir ve matrix ise artık birim matrise dönmüştür
    printf("\nTers matris:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%8.4lf ", unit_matrix[i][j]);
        }
        printf("\n");
    }

    // Belleği temizle
    for (i = 0; i < N; i++) {
        free(matrix[i]);
        free(unit_matrix[i]);
    }
    free(matrix);
    free(unit_matrix);
}

void cholesky_method() {

    // matrisler için declarationlar
    int n;
    int i, j, k;
    double sum;


    printf("Matris boyutunu girin (örn: 3): ");
    scanf("%d", &n);
    
    // Bellek ayır
    double** main_matrix = (double**)malloc(n * sizeof(double*));
    double** lower_matrix = (double**)calloc(n, sizeof(double*));
    double* answer = (double*)malloc(n * sizeof(double));
    double* y = (double*)malloc(n * sizeof(double));
    double* x = (double*)malloc(n * sizeof(double));
    
    for (i = 0; i < n; i++) {
        main_matrix[i] = (double*)malloc(n * sizeof(double));
        lower_matrix[i] = (double*)calloc(n, sizeof(double));
    }
    
    // Matris A'yı al
    printf("Simetrik ve pozitif tanımlı matris A'nın elemanlarını girin:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%lf", &main_matrix[i][j]);
    
    // Cholesky Ayrıştırması: A = L * L^T
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
             sum = 0;
            
            if (j == i) { // Diagonal eleman
                for (k = 0; k < j; k++) {
                    sum += lower_matrix[j][k] * lower_matrix[j][k];
                }
                lower_matrix[j][j] = sqrt(main_matrix[j][j] - sum);
            } else { // Alt üçgensel eleman
                for (k = 0; k < j; k++) {
                    sum += lower_matrix[i][k] * lower_matrix[j][k];
                }
                lower_matrix[i][j] = (main_matrix[i][j] - sum) / lower_matrix[j][j];
            }
        }
    }
    
    // L matrisi (alt üçgensel)
    printf("\nCholesky Alt Üçgensel Matris (L):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%.4f ", lower_matrix[i][j]);
        printf("\n");
    }
    
    // Üst üçgensel matris L^T yazdır
    printf("\nCholesky Üst Üçgensel Matris (L^T):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%.4f ", (j >= i) ? lower_matrix[j][i] : 0.0);  // Transpoz
        printf("\n");
    }
    
    // b vektörünü al
    printf("\nSonuç vektörünü (b) girin:\n");
    for (i = 0; i < n; i++)
        scanf("%lf", &answer[i]);
    
    // Adım 1: L * y = b (İleri yerine koyma)
    for (i = 0; i < n; i++) {
        double sum = 0;
        for (k = 0; k < i; k++)
            sum += lower_matrix[i][k] * y[k];
        y[i] = (answer[i] - sum) / lower_matrix[i][i];
    }
    
    // Adım 2: L^T * x = y (Geri yerine koyma)
    for (i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (k = i + 1; k < n; k++)
            sum += lower_matrix[k][i] * x[k];  // L^T[i][k] = L[k][i]
        x[i] = (y[i] - sum) / lower_matrix[i][i];
    }
    
    // Çözüm vektörü x
    printf("\nÇözüm vektörü (x):\n");
    for (i = 0; i < n; i++)
        printf("x[%d] = %.4f\n", i, x[i]);
    
    // Belleği temizle
    for (i = 0; i < n; i++) {
        free(main_matrix[i]);
        free(lower_matrix[i]);
    }
    free(main_matrix);
    free(lower_matrix);
    free(answer);
    free(y);
    free(x);
}

void gauss_seidel_method() {
    int n;  // Denklem sayısı
    double **coef_matrix = NULL;  // Katsayı matrisi
    double *constants = NULL;     // Sağ taraf sabitleri
    double *x = NULL;             // Çözüm vektörü
    double *x_prev = NULL;        // Önceki çözüm vektörü
    double epsilon;               // Yakınsama kriteri
    int max_iterations;           // Maksimum iterasyon sayısı
    int i, j,k;
    char equation[256];           // Denklem dizisi
    char *ptr;
    double coef;
    int var_index;
    int max_row;
    double max_val;
    double *temp_row;
    double temp_const;

        // İterasyon değişkenlerini sıfırla
        int iterations = 0;
        int converged = 0;
        double sum;
        double max_error;
    
    // Denklem sayısını al
    printf("Denklem sayısını giriniz: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Geçersiz giriş! Denklem sayısı pozitif bir tamsayı olmalı.\n");
        return;
    }

    // Bellek ayır
    coef_matrix = (double **)malloc(n * sizeof(double *));
    if (!coef_matrix) {
        printf("Bellek ayırma hatası!\n");
        return;
    }
    for (i = 0; i < n; i++) {
        coef_matrix[i] = (double *)calloc(n, sizeof(double));
        if (!coef_matrix[i]) {
            printf("Bellek ayırma hatası!\n");
            free_memory(coef_matrix, constants, x, x_prev, i);
            return;
        }
    }
    constants = (double *)malloc(n * sizeof(double));
    x = (double *)calloc(n, sizeof(double));
    x_prev = (double *)calloc(n, sizeof(double));
    if (!constants || !x || !x_prev) {
        printf("Bellek ayırma hatası!\n");
        free_memory(coef_matrix, constants, x, x_prev, n);
        return;
    }

    // Denklemleri al
    printf("Denklemleri giriniz (örn: '3x1+2x2-x3'):\n");
    for (i = 0; i < n; i++) {
        printf("Denklem %d: ", i + 1);
        if (scanf("%s", equation) != 1) {
            printf("Geçersiz giriş!\n");
            free_memory(coef_matrix, constants, x, x_prev, n);
            return;
        }
        ptr = equation;

        // Tüm katsayıları 0 olarak başlat
        for ( k = 0; k < n; k++) {
            coef_matrix[i][k] = 0.0;
        }

        while (*ptr) {
            coef = 1.0;

            // İşaret kontrolü
            if (*ptr == '+' || *ptr == '-') {

                if (*ptr == '+')
                {
                   coef=1.0;
                }
                else{
                    coef= -1.0;
                }
                ptr++;
            }

            // Katsayıyı al
            if (*ptr >= '0' && *ptr <= '9') {
                // verilen string içinde katsayının float olmasına karşın atof ile chardan double veri tipine geçiş sağlanır
                coef *= atof(ptr);
                // sayı bitine kadar devam et
                while (*ptr >= '0' && *ptr <= '9' || *ptr == '.') ptr++;
            }

            // Değişkeni oku
            if (*ptr == 'x' || *ptr == 'X') {
                ptr++;
                // x gördüğünde ptr bir adım ileri gider
                // bu sayede atoi x in indisini alır
                var_index = atoi(ptr) - 1;
                if (var_index >= 0 && var_index < n) {
                    coef_matrix[i][var_index] = coef;
                } else {
                    printf("Hata: Geçersiz değişken indeksi (x%d)!\n", var_index + 1);
                    free_memory(coef_matrix, constants, x, x_prev, n);
                    return;
                }
                while (*ptr >= '0' && *ptr <= '9') ptr++;
            } else if (*ptr) {
                ptr++;
            }
        }
    }

    // Sabit değerleri al
    printf("Denklemlerin sağ tarafındaki sabitleri giriniz:\n");
    for (i = 0; i < n; i++) {
        printf("Denklem %d için sabit: ", i + 1);
        if (scanf("%lf", &constants[i]) != 1) {
            printf("Geçersiz giriş!\n");
            free_memory(coef_matrix, constants, x, x_prev, n);
            return;
        }
    }

    // Diagonal elemanı maksimize etmek için satır değişimi
    for (i = 0; i < n; i++) {
         max_row = i;
         max_val = fabs(coef_matrix[i][i]);
        for (j = i + 1; j < n; j++) {
            if (fabs(coef_matrix[j][i]) > max_val) {
                max_val = fabs(coef_matrix[j][i]);
                max_row = j;
            }
        }

        // Satır değişimi gerekiyorsa uygula
        if (max_row != i) {
           temp_row = coef_matrix[i];
            coef_matrix[i] = coef_matrix[max_row];
            coef_matrix[max_row] = temp_row;

             temp_const = constants[i];
            constants[i] = constants[max_row];
            constants[max_row] = temp_const;

            printf("Satır %d ile satır %d değiştirildi.\n", i + 1, max_row + 1);
        }
    }

    // Gauss-Seidel parametreleri
    printf("\nEpsilon değerini giriniz: ");
    if (scanf("%lf", &epsilon) != 1 || epsilon <= 0) {
        printf("Geçersiz giriş! Epsilon pozitif bir sayı olmalı.\n");
        free_memory(coef_matrix, constants, x, x_prev, n);
        return;
    }

    printf("Maksimum iterasyon sayısını giriniz: ");
    if (scanf("%d", &max_iterations) != 1 || max_iterations <= 0) {
        printf("Geçersiz giriş! Maksimum iterasyon sayısı pozitif bir tamsayı olmalı.\n");
        free_memory(coef_matrix, constants, x, x_prev, n);
        return;
    }

    
        // İlk tahmin değerlerini al
        printf("\nBaşlangıç tahmin değerlerini giriniz:\n");
        for (i = 0; i < n; i++) {
            printf("x%d için başlangıç tahmini: ", i + 1);
            if (scanf("%lf", &x[i]) != 1) {
                printf("Geçersiz giriş!\n");
                free_memory(coef_matrix, constants, x, x_prev, n);
                return;
            }
        }

        // Katsayı matrisi kontrolü için ekran çıktısı
        printf("\nKatsayı matrisi:\n");
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                printf("%8.4lf ", coef_matrix[i][j]);
            }
            printf("| %8.4lf\n", constants[i]);
        }

 

        // Gauss-Seidel iterasyonları
        printf("\nGauss-Seidel İterasyonları:\n");

        while (!converged && iterations < max_iterations) {
            // Önceki iterasyonun değerlerini sakla
            for (i = 0; i < n; i++) {
                x_prev[i] = x[i];
            }

            // Gauss-Seidel iterasyonu
            int valid_iteration = 1;
            for (i = 0; i < n; i++) {
                sum = constants[i];
                for (j = 0; j < n; j++) {
                    if (j != i) {
                        sum -= coef_matrix[i][j] * x[j];
                    }
                }

                if (fabs(coef_matrix[i][i]) > 1e-10) {  // Sıfıra bölme kontrolü için daha güvenli
                    x[i] = sum / coef_matrix[i][i];
                } else {
                    printf("Uyarı: %d. denklemin köşegen elemanı sıfıra çok yakın (%lf). Bu denklem için çözüm hesaplanamadı.\n", 
                           i + 1, coef_matrix[i][i]);
                    x[i] = x_prev[i]; // Önceki değeri koru
                    valid_iteration = 0; // İterasyonun geçerli olmadığını işaretle
                }
            }
           
            iterations++;

            // Her iterasyonun sonucunu yazdır
            printf("İterasyon %d:\n", iterations);
            for (i = 0; i < n; i++) {
                printf("x%d = %lf\n", i + 1, x[i]);
            }

            // Yakınsama kontrolü
            if (valid_iteration) {
                max_error = 0.0;
                for (i = 0; i < n; i++) {
                    double error = fabs(x[i] - x_prev[i]);
                    if (error > max_error) {
                        max_error = error;
                    }
                }
                // Tüm değişkenler için hata epsilon'dan küçükse yakınsama var demektir
                if (max_error < epsilon) {
                    converged = 1;
                    printf("\nÇözüm yakınsadı! Maksimum hata: %lf (epsilon: %lf)\n", max_error, epsilon);
                } else {
                    printf("Mevcut maksimum hata: %lf\n", max_error);
                }
            }
        }
        // Sonuçları yazdır
        if (!converged) {
            printf("\nMaksimum iterasyon sayısına ulaşıldı (%d iterasyon), çözüm yakınsamadı.\n", max_iterations);
        } else {
            printf("\nSonuç (iterasyon sayısı: %d):\n", iterations);
            for (i = 0; i < n; i++) {
                printf("x%d = %lf\n", i + 1, x[i]);
            }
        }

    // Belleği temizle
    free_memory(coef_matrix, constants, x, x_prev, n);
}

void derivative() {
    double forward_derivative;
    double backward_derivative;
    double central_derivative;
    char *temp, *input;
    int index, token_count = 0;
    Node* root;
    double x_value = 0.0, epsilon;
    int x_asked = 1;
    double value1, value2, value3, f_value;
    int control = 1, iteration = 0;
    
    // Kullanıcıdan ifade al
    temp = (char*)calloc(256, sizeof(char));
    printf("Matematiksel ifadeyi girin: ");
    scanf("%s", temp);
    input = (char*)calloc(strlen(temp) + 1, sizeof(char));
    strcpy(input, temp);
    free(temp);
    
    // Tokenize et ve parse et
    Token *tokens = (Token*)calloc(100, sizeof(Token));
    tokenize(input, tokens, &token_count);
    free(input);
    
    index = 0;
    root = parse_expression(tokens, &index, token_count);
    free(tokens);
    
    if (root == NULL) {
        printf("İfade ayrıştırılamadı\n");
        return;
    }
    
    printf("x değerini gir: ");
    scanf("%lf", &x_value);
    printf("h değerini giriniz: ");
    scanf("%lf",&epsilon);
    
    // Fonksiyonun x değerindeki değeri
    f_value = evaluate(root, &x_value, &x_asked);
    printf("\nFonksiyon değeri f(%lf) = %lf\n", x_value, f_value);
    
    // İleri türev hesaplama
    printf("\nİleri türev hesaplanıyor:\n");
    value1 = x_value + epsilon;
    value2 = x_value;
    forward_derivative = (evaluate(root, &value1, &x_asked) - evaluate(root, &value2, &x_asked)) / epsilon;
    printf("İleri türev = %lf\n", forward_derivative);
    
    // Geri türev hesaplama
    printf("\nGeri türev hesaplanıyor:\n");
    value1 = x_value;
    value2 = x_value - epsilon;
    backward_derivative = (evaluate(root, &value1, &x_asked) - evaluate(root, &value2, &x_asked)) / epsilon;
    printf("Geri türev = %lf\n", backward_derivative);
    
    // Merkezi türev hesaplama
    printf("\nMerkezi türev hesaplanıyor:\n");
    value1 = x_value + epsilon;
    value2 = x_value - epsilon;
    central_derivative = (evaluate(root, &value1, &x_asked) - evaluate(root, &value2, &x_asked)) / (2 * epsilon);
    printf("Merkezi türev = %lf\n", central_derivative);
    

    // Karşılaştırma ve hata analizi
    printf("\nSayısal Türev Sonuçları\n");
    printf("x = %lf için:\n", x_value);
    printf("İleri türev: %lf\n", forward_derivative);
    printf("Geri türev: %lf\n", backward_derivative);
    printf("Merkezi türev: %lf (En doğru sonuç)\n", central_derivative);
    
    // Belleği temizle
    free_tree(root);
}

void simpson_method() {
    
    // tokenizer için declaration
    char *temp, *input;
    int index, token_count = 0;
    Node* root;
    int x_asked = 1;

    // simpson için declaration
    double derivative, value1, value2, f_value;
    double first, end;
    int count;
    double simpson_1, simpson_2;
    int i;
    double h;
    double one;
    double last;
    double sum_odd = 0.0;
    double sum_even = 0.0;
    double x;
    double sum_3k1 = 0.0; 
    double sum_3k2 = 0.0; 
    double sum_3k3 = 0.0; 



    // Kullanıcıdan ifade al
    temp = (char*)calloc(256, sizeof(char));
    printf("Matematiksel ifadeyi girin: ");
    scanf("%s", temp);
    input = (char*)calloc(strlen(temp) + 1, sizeof(char));
    strcpy(input, temp);
    free(temp);
    
    // Tokenize et ve parse et
    Token *tokens = (Token*)calloc(100, sizeof(Token));
    tokenize(input, tokens, &token_count);
    free(input);
    
    index = 0;
    root = parse_expression(tokens, &index, token_count);
    free(tokens);
    
    if (root == NULL) {
        printf("İfade ayrıştırılamadı\n");
        return;
    }
    
    printf("Simpson 1/3 metodu:\n");
    printf("Başlangıç ve bitiş değerlerini girin (a b): ");
    scanf("%lf %lf", &first, &end);
    
    // simpson 1/3 için aralık sayısı çift olmalı
    do
    {
           printf("Kaç aralığa bölünsün? (Çift sayı olmalı): ");
           scanf("%d", &count);
           if (count % 2 != 0)
           {
             printf("Aralık sayısı çift olmalıdır.");
           }
    } while (count % 2 != 0);
    
 
    
    // Adım boyutunu hesapla
   h = (end - first) / count;
    
    // İlk ve son değerleri hesapla
 one = evaluate(root, &first, &x_asked);
 last = evaluate(root, &end, &x_asked);
    
    // 4 ile çarpılacak ve 2 ile çarpılacak terimlerin toplamını hesapla
 sum_odd = 0.0;  // Tek indeksli noktalar (4 ile çarpılacak)
 sum_even = 0.0; // Çift indeksli noktalar (2 ile çarpılacak)
    
    for (i = 1; i < count; i++) {
         x = first + i * h;
        if (i % 2 == 1) { // Tek indeksli noktalar
            sum_odd += evaluate(root, &x, &x_asked);
        } else { // Çift indeksli noktalar
            sum_even += evaluate(root, &x, &x_asked);
        }
    }
    
    // Simpson 1/3 formülünü uygula
    simpson_1 = (h / 3.0) * (one + 4.0 * sum_odd + 2.0 * sum_even + last);
    
    printf("Simpson 1/3 integral değeri: %lf\n", simpson_1);

            do
          {
             printf("Kaç aralığa bölünsün? (Çift sayı olmalı): ");
             scanf("%d", &count);
           if (count % 3 != 0)
           {
              printf("Simpson 3/8 için aralık sayısı 3'ün katı olmalıdır");
           }
    } while (count % 3 != 0);

  h = (end - first) / count;
            
             sum_3k1 = 0.0; // 3k+1 indeksli noktalar
             sum_3k2 = 0.0; // 3k+2 indeksli noktalar
             sum_3k3 = 0.0; // 3k+3 indeksli noktalar (3'ün katı)
            
            for (i = 1; i < count; i++) {
                   x = first + i * h;
                if (i % 3 == 1) {
                    sum_3k1 += evaluate(root, &x, &x_asked);
                } else if (i % 3 == 2) {
                    sum_3k2 += evaluate(root, &x, &x_asked);
                } else if (i % 3 == 0) {
                    sum_3k3 += evaluate(root, &x, &x_asked);
                }
            }
            // Simpson 3/8 formülünü uygula
            simpson_2 = (3.0 * h / 8.0) * (one + 3.0 * sum_3k1 + 3.0 * sum_3k2 + 2.0 * sum_3k3 + last);
            printf("Simpson 3/8 integral değeri: %lf\n", simpson_2); 

    // Belleği temizle
    free_tree(root);
}

void trapez_method() {

    // tokenizer için declaration
    char *temp, *input;
    int index, token_count = 0;
    Node* root;
    int x_asked = 1;

     // trapez için declaration
    int i,j;
    double value1, value2, f_value;
    double first, end;
    int count;
    double mid = 0, trapez;
    double first_value;
    double end_value;
    double h,x;
    
    // Kullanıcıdan ifade al
    temp = (char*)calloc(256, sizeof(char));
    printf("Matematiksel ifadeyi girin: ");
    scanf("%s", temp);
    input = (char*)calloc(strlen(temp) + 1, sizeof(char));
    strcpy(input, temp);
    free(temp);
    
    // Tokenize et ve parse et
    Token *tokens = (Token*)calloc(100, sizeof(Token));
    tokenize(input, tokens, &token_count);
    free(input);
    
    index = 0;
    root = parse_expression(tokens, &index, token_count);
    free(tokens);
    
    if (root == NULL) {
        printf("İfade ayrıştırılamadı\n");
        return;
    }

    printf("Başlangıç ve bitiş değerlerini girin (a b): ");
    scanf("%lf %lf", &first, &end);
    
    printf("Aralık sayısını girin: ");
    scanf("%d", &count);  // Added this line to get the number of intervals
    
     h = (end - first) / count;
    
    // İlk ve son noktaların değerlerini hesapla
     first_value = evaluate(root, &first, &x_asked);
     end_value = evaluate(root, &end, &x_asked);
    
    // Orta noktaların toplamını hesapla
    for (i = 1; i < count; i++) {
         x = first + (i * h);
        mid += evaluate(root, &x, &x_asked);
    }
    
    // Trapezoidal formülü doğru şekilde uygula
    trapez = h * ((first_value + end_value) / 2 + mid);
    
    printf("Integral değeri: %lf\n", trapez);
    
    // Node yapısını temizle (free_node fonksiyonunuz varsa çağırın)
    // free_node(root);
}

void gregory_newton_method() {
    // tokenizer için declaration
    char *temp, *input;
    int index, token_count = 0;
    Node* root;
    int x_asked = 1;

    // gregory için declaration
    int i, j, k;
    int count;
    double **forward_difference;
    double x_value;
    double new_x;
    double base_x;
    double sum;
    double* x_values;
    double h;
    double theta,term;


    // Kullanıcıdan ifade al
    temp = (char*)calloc(256, sizeof(char));
    printf("Matematiksel ifadeyi girin: ");
    scanf("%s", temp);

    input = (char*)calloc(strlen(temp) + 1, sizeof(char));
    strcpy(input, temp);
    free(temp);

    // Tokenize ve parse işlemleri
    Token *tokens = (Token*)calloc(100, sizeof(Token));
    tokenize(input, tokens, &token_count);
    free(input);

    index = 0;
    root = parse_expression(tokens, &index, token_count);
    free(tokens);

    if (root == NULL) {
        printf("İfade ayrıştırılamadı\n");
        return;
    }

    // Veri girişi
    printf("Kaç adet x değeri gireceksiniz?\n");
    scanf("%d", &count);

    x_values = (double*)calloc(count, sizeof(double));
    forward_difference = (double**)calloc(count, sizeof(double*));
    for (i = 0; i < count; i++) {
        forward_difference[i] = (double*)calloc(count, sizeof(double));
    }

    printf("X değerlerini giriniz:\n");
    for (i = 0; i < count; i++) {
        scanf("%lf", &x_values[i]);
        if (i == 0) {
            base_x = x_values[i]; // ilk x değeri sabit alınır
        }
        x_value = x_values[i];
        forward_difference[i][0] = evaluate(root, &x_value, &x_asked);
        printf("f(x%d) = %lf\n", i, forward_difference[i][0]);
    }

    // İleri farkları hesapla
    for (j = 1; j < count; j++) {
        for (i = 0; i < count - j; i++) {
            forward_difference[i][j] = forward_difference[i + 1][j - 1] - forward_difference[i][j - 1];
        }
    }

    // Tahmin yapılacak x değeri alınır
    printf("Yaklaşık değer hesaplamak istediğiniz x değerini girin:\n");
    scanf("%lf", &new_x);

    // Gregory-Newton toplamı hesaplanır
    sum = forward_difference[0][0];
     h = x_values[1] - x_values[0]; // Sabit adım genişliği
    theta = (new_x - base_x) / h;

    for (i = 1; i < count; i++) {
         term = 1.0;
        // Theta terimini hesapla
        for (j = 0; j < i; j++) {
            term *= (theta - j);
        }
        
        // Faktöriyel hesapla
        int factorial = 1;
        for (j = 1; j <= i; j++) {
            factorial *= j;
        }
        
        // Terim hesaplaması
        sum += (term / factorial) * forward_difference[0][i];
    }

    printf("Gregory-Newton ile yaklaşık f(%lf) = %lf\n", new_x, sum);

    // memory serbest bırak
    for (i = 0; i < count; i++) {
        free(forward_difference[i]);
    }
    free(forward_difference);
    free(x_values);
}