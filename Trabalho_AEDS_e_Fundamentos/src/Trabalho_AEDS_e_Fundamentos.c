#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct Cliente {
    int id;
    char nome[50];
    char endereco[60];
    int telefone;
};

struct Funcionario {
    int id;
    char nome[50];
    int telefone;
    char cargo[30];
    float salario;
};

struct Estadia {
    int id;
    int dataEntrada;    // formato yyyymmdd
    int dataSaida;      // formato yyyymmdd
    int diarias;        // quantidade de diárias
    int idCliente;
    int numeroQuarto;
};

// Função para gerar um ID único para cada cliente
int gerarIdUnico(struct Cliente clientes[], int contadorClientes) {
    int novoId;
    int idExistente;

    do {
        novoId = rand() % 100 + 1;
        idExistente = 0;

        // Verifica se o novoId já existe
        for (int i = 0; i < contadorClientes; i++) {
            if (clientes[i].id == novoId) {
                idExistente = 1;
                break;
            }
        }
    } while (idExistente);

    return novoId;
}

// Função para gerar um ID único para cada funcionário
int gerarIdUnicoFuncionario(struct Funcionario funcionarios[], int contadorFuncionarios) {
    int idFuncionario;
    int idFuncionarioExistente;

    do {
        idFuncionario = rand() % 100 + 1;
        idFuncionarioExistente = 0;
        for (int i = 0; i < contadorFuncionarios; i++) {
            if (funcionarios[i].id == idFuncionario) {
                idFuncionarioExistente = 1;
                break;
            }
        }

    } while (idFuncionarioExistente);

    return idFuncionario;
}

// Função para calcular a diferença de dias entre duas datas no formato yyyymmdd
int calcularDiferencaDias(int dataEntrada, int dataSaida) {
    struct tm tmEntrada = {0};
    struct tm tmSaida = {0};

    tmEntrada.tm_year = dataEntrada / 10000 - 1900;
    tmEntrada.tm_mon = (dataEntrada % 10000) / 100 - 1;
    tmEntrada.tm_mday = dataEntrada % 100;

    tmSaida.tm_year = dataSaida / 10000 - 1900;
    tmSaida.tm_mon = (dataSaida % 10000) / 100 - 1;
    tmSaida.tm_mday = dataSaida % 100;

    time_t entrada = mktime(&tmEntrada);
    time_t saida = mktime(&tmSaida);

    if (entrada == (time_t)(-1) || saida == (time_t)(-1)) {
        return -1; // erro ao converter datas
    }

    double diferencaSegundos = difftime(saida, entrada);
    int diferencaDias = diferencaSegundos / (60 * 60 * 24);

    return diferencaDias;
}

// Função para cadastrar um novo cliente
void cadastroCliente(struct Cliente clientes[], int *contadorClientes, int numMaxClientes) {
    if (*contadorClientes < numMaxClientes) {
        int i = *contadorClientes;

        clientes[i].id = gerarIdUnico(clientes, *contadorClientes); // Gerar ID único

        printf("Insira o nome do cliente: ");
        fflush(stdout); // Limpa o buffer de saída
        scanf(" %[^\n]", clientes[i].nome);

        printf("Insira o endereço: ");
        fflush(stdout); // Limpa o buffer de saída
        scanf(" %[^\n]", clientes[i].endereco);

        printf("Insira o telefone de contato: ");
        fflush(stdout); // Limpa o buffer de saída
        scanf(" %d", &clientes[i].telefone);

        (*contadorClientes)++; // Incrementa o contador de clientes

        // Salvar clientes em arquivo após cada cadastro
        FILE *arquivo;
        arquivo = fopen("clientes.txt", "a");

        if (arquivo != NULL) {
            fprintf(arquivo, "%d;%s;%s;%d\n", clientes[i].id, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
            fclose(arquivo);
        } else {
            printf("Erro ao salvar cliente no arquivo.\n");
        }
    } else {
        printf("Limite máximo de clientes atingido.\n");
    }
}

// Função para cadastrar um novo funcionário
void cadastroFuncionario(struct Funcionario funcionarios[], int *contadorFuncionarios, int numMaxFuncionarios) {
    if (*contadorFuncionarios < numMaxFuncionarios) {
        int i = *contadorFuncionarios;

        funcionarios[i].id = gerarIdUnicoFuncionario(funcionarios, *contadorFuncionarios);

        printf("Insira o nome do funcionário: ");
        fflush(stdout); // Limpa o buffer de saída
        scanf(" %[^\n]", funcionarios[i].nome);

        printf("Insira o telefone do funcionário: ");
        fflush(stdout); // Limpa o buffer de saída
        scanf(" %d", &funcionarios[i].telefone);

        printf("Insira o cargo do funcionário: ");
        fflush(stdout); // Limpa o buffer de saída
        scanf(" %[^\n]", funcionarios[i].cargo);

        printf("Insira o salário do funcionário: ");
        fflush(stdout); // Limpa o buffer de saída
        scanf(" %f", &funcionarios[i].salario);

        (*contadorFuncionarios)++; // Incrementa o contador de funcionários

        // Salvar funcionários em arquivo após cada cadastro
        FILE *arquivo;
        arquivo = fopen("funcionarios.txt", "a");

        if (arquivo != NULL) {
            fprintf(arquivo, "%d;%s;%d;%s;%.2f\n", funcionarios[i].id, funcionarios[i].nome, funcionarios[i].telefone,
                    funcionarios[i].cargo, funcionarios[i].salario);
            fclose(arquivo);
        } else {
            printf("Erro ao salvar funcionário no arquivo.\n");
        }
    } else {
        printf("Limite máximo de funcionários atingido.\n");
    }
}

// Função para cadastrar uma nova estadia
void cadastroEstadia(struct Estadia estadias[], int *contadorEstadias, int numMaxEstadias) {
    if (*contadorEstadias < numMaxEstadias) {
        int i = *contadorEstadias;

        estadias[i].id = *contadorEstadias + 1;

        printf("Insira a data de entrada (yyyymmdd): ");
        scanf("%d", &estadias[i].dataEntrada);

        printf("Insira a data de saída (yyyymmdd): ");
        scanf("%d", &estadias[i].dataSaida);

        estadias[i].diarias = calcularDiferencaDias(estadias[i].dataEntrada, estadias[i].dataSaida);

        printf("Insira o ID do cliente: ");
        scanf("%d", &estadias[i].idCliente);

        printf("Insira o número do quarto: ");
        scanf("%d", &estadias[i].numeroQuarto);

        (*contadorEstadias)++; // Incrementa o contador de estadias

        // Salvar estadias em arquivo após cada cadastro
        FILE *arquivo;
        arquivo = fopen("estadias.txt", "a");

        if (arquivo != NULL) {
            fprintf(arquivo, "%d;%d;%d;%d;%d;%d\n", estadias[i].id, estadias[i].dataEntrada, estadias[i].dataSaida,
                    estadias[i].diarias, estadias[i].idCliente, estadias[i].numeroQuarto);
            fclose(arquivo);
        } else {
            printf("Erro ao salvar estadia no arquivo.\n");
        }
    } else {
        printf("Limite máximo de estadias atingido.\n");
    }
}

// Função para listar todos os clientes cadastrados
void listarClientes(struct Cliente clientes[], int contadorClientes) {
    printf("\nLista de Clientes:\n");
    for (int i = 0; i < contadorClientes; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("ID: %d\n", clientes[i].id);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Endereço: %s\n", clientes[i].endereco);
        printf("Telefone: %d\n\n", clientes[i].telefone);
    }
}

// Função para pesquisar cliente pelo nome
void pesquisarClientes(struct Cliente clientes[], int contadorClientes) {
    char nome[50];
    printf("Pesquisar cliente pelo nome:\n");
    printf("Nome do cliente: ");
    fflush(stdout);
    scanf(" %[^\n]", nome);

    for (int i = 0; i < contadorClientes; i++) {
        if (strcmp(clientes[i].nome, nome) == 0) {
            printf("Cliente encontrado:\n");
            printf("ID: %d\n", clientes[i].id);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Endereço: %s\n", clientes[i].endereco);
            printf("Telefone: %d\n\n", clientes[i].telefone);
            return;
        }
    }

    printf("Cliente não encontrado.\n");
}

int main(void) {
    srand(time(NULL)); // Inicializar semente para geração de números aleatórios

    int escolha; // escolha da função pelo usuário;
    int contadorClientes = 0; // contador de clientes cadastrados
    int contadorFuncionarios = 0; // contador de funcionários cadastrados
    int contadorEstadias = 0; // contador de estadias cadastradas
    struct Cliente clientes[100]; // array de struct Clientes;
    struct Funcionario funcionarios[100]; // array de struct Funcionarios;
    struct Estadia estadias[100]; // array de struct Estadias;

    // Carregar dados salvos (se existirem)
    FILE *arquivo;
    arquivo = fopen("clientes.txt", "r");

    if (arquivo != NULL) {
        while (fscanf(arquivo, "%d;%[^;];%[^;];%d\n", &clientes[contadorClientes].id, clientes[contadorClientes].nome,
                      clientes[contadorClientes].endereco, &clientes[contadorClientes].telefone) == 4) {
            contadorClientes++;
        }
        fclose(arquivo);
    } else {
        printf("Arquivo de clientes não encontrado ou não pode ser aberto.\n");
    }

    arquivo = fopen("funcionarios.txt", "r");

    if (arquivo != NULL) {
        while (fscanf(arquivo, "%d;%[^;];%d;%[^;];%f\n", &funcionarios[contadorFuncionarios].id, funcionarios[contadorFuncionarios].nome,
                      &funcionarios[contadorFuncionarios].telefone, funcionarios[contadorFuncionarios].cargo, &funcionarios[contadorFuncionarios].salario) == 5) {
            contadorFuncionarios++;
        }
        fclose(arquivo);
    } else {
        printf("Arquivo de funcionários não encontrado ou não pode ser aberto.\n");
    }

    arquivo = fopen("estadias.txt", "r");

    if (arquivo != NULL) {
        while (fscanf(arquivo, "%d;%d;%d;%d;%d;%d\n", &estadias[contadorEstadias].id, &estadias[contadorEstadias].dataEntrada,
                      &estadias[contadorEstadias].dataSaida, &estadias[contadorEstadias].diarias, &estadias[contadorEstadias].idCliente,
                      &estadias[contadorEstadias].numeroQuarto) == 6) {
            contadorEstadias++;
        }
        fclose(arquivo);
    } else {
        printf("Arquivo de estadias não encontrado ou não pode ser aberto.\n");
    }

    // Loop principal
    do {
        printf("\nO que você deseja fazer?\n\n");
        printf("1-Cadastrar cliente\n");
        printf("2-Cadastrar funcionário\n");
        printf("3-Cadastrar estadia\n");
        printf("4-Dar baixa em uma estadia\n");
        printf("5-Pesquisar cliente pelo nome\n");
        printf("6-Estadias de um cliente\n");
        printf("7-Listar clientes\n");
        printf("0-Sair\n\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                cadastroCliente(clientes, &contadorClientes, 100);
                break;
            case 2:
                cadastroFuncionario(funcionarios, &contadorFuncionarios, 100);
                break;
            case 3:
                cadastroEstadia(estadias, &contadorEstadias, 100);
                break;
            case 4:
                // Implementar baixa em estadia
                break;
            case 5:
                pesquisarClientes(clientes, contadorClientes);
                break;
            case 6:
                // Implementar estadias do cliente
                break;
            case 7:
                listarClientes(clientes, contadorClientes);
                break;
        }

    } while (escolha != 0);

    return 0;
}
