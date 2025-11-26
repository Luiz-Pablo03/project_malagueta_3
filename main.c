#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- DEFINIÇÕES E ESTRUTURAS ---

#define MAX_PROFISSOES 50
#define MAX_PROFISSIONAIS 200
#define MAX_CLIENTES 300
#define MAX_ATENDIMENTOS 2000

// Nomes dos arquivos para persistência de dados
#define ARQUIVO_PROFISSOES "profissoes.dat"
#define ARQUIVO_PROFISSIONAIS "profissionais.dat"
#define ARQUIVO_CLIENTES "clientes.dat"
#define ARQUIVO_ATENDIMENTOS "atendimentos.dat"

struct Data {
  int dia, mes, ano;
};

struct Profissao {
  int codigo;
  char nome[50];
  char sigla[10];
};

struct Profissional {
  int matricula;
  char cpf[20];
  char nome[80];
  int prof_codigo;
  char numRP[20];
  char tipo[40];
  struct Data nascimento;
  char email[80];
  char fone[20];
};

struct Cliente {
  int codigo;
  char nome[80];
  struct Data nascimento;
  int idade;
  char email[80];
  char fone[20];
  char celular[20];
  char endereco[150];
};

struct Atendimento {
  int numero;
  int prof_matricula;
  int cliente_codigo;
  struct Data data;
  char descricao[200];
};

// Arrays globais para armazenar os dados em memória
struct Profissao profissoes[MAX_PROFISSOES];
struct Profissional profissionais[MAX_PROFISSIONAIS];
struct Cliente clientes[MAX_CLIENTES];
struct Atendimento atendimentos[MAX_ATENDIMENTOS];

// Contadores para a quantidade de registros em cada array
int qtdProfissoes = 0;
int qtdProfissionais = 0;
int qtdClientes = 0;
int qtdAtendimentos = 0;

// --- FUNÇÕES UTILITÁRIAS ---

void clrscr() {
  system("cls");
}

void titulo(const char txt[]) {
  clrscr();
  printf("=== %s ===\n", txt);
}

void pause() {
  printf("\nPressione Enter para continuar...");
  getchar();
}

void limparEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {}
}

void lerLinha(char *s, int tam) {
  if (tam <= 0) return;
  fgets(s, tam, stdin);
  s[strcspn(s, "\n")] = 0;
}

int lerInt(const char prompt[]) {
  int x;
  int ok = 0;
  do {
    printf("%s", prompt);
    if (scanf("%d", &x) == 1) {
      ok = 1;
    } else {
      printf("Entrada invalida. Digite um numero.\n");
    }
    limparEntrada();
  } while (!ok);
  return x;
}

struct Data lerData() {
  struct Data d;
  int valida = 0;
  do {
      printf("Dia: ");
      scanf("%d", &d.dia);
      printf("Mes: ");
      scanf("%d", &d.mes);
      printf("Ano: ");
      scanf("%d", &d.ano);
      limparEntrada();

      if (d.dia < 1 || d.dia > 31 || d.mes < 1 || d.mes > 12 || d.ano < 1) {
          printf("Data invalida (Dia 1-31, Mes 1-12). Digite novamente.\n");
      } else {
          valida = 1;
      }
  } while (!valida);
  return d;
}

// --- FUNÇÕES DE BUSCA (USANDO PONTEIROS) ---

// Retorna um ponteiro para a profissão encontrada ou NULL se não existir
struct Profissao* encontrarProfissaoPorCodigo(int codigo) {
  struct Profissao *p;
  for (p = profissoes; p < profissoes + qtdProfissoes; p++) {
    if (p->codigo == codigo) return p;
  }
  return NULL;
}

// Retorna um ponteiro para o profissional encontrado ou NULL se não existir
struct Profissional* encontrarProfissionalPorMatricula(int mat) {
  struct Profissional *p;
  for (p = profissionais; p < profissionais + qtdProfissionais; p++) {
    if (p->matricula == mat) return p;
  }
  return NULL;
}

// Retorna um ponteiro para o cliente encontrado ou NULL se não existir
struct Cliente* encontrarClientePorCodigo(int cod) {
  struct Cliente *c;
  for (c = clientes; c < clientes + qtdClientes; c++) {
    if (c->codigo == cod) return c;
  }
  return NULL;
}


// --- FUNÇÕES DE EXIBIÇÃO (USANDO PONTEIROS) ---

void mostrarProfissoes() {
  printf("\nProfissoes cadastradas:\n");
  if (qtdProfissoes == 0) {
      printf("Nenhuma profissao cadastrada.\n");
      return;
  }
  struct Profissao *p;
  for (p = profissoes; p < profissoes + qtdProfissoes; p++) {
    printf("Codigo %d | %s (%s)\n", p->codigo, p->nome, p->sigla);
  }
}

void mostrarProfissionais() {
  printf("\nProfissionais cadastrados:\n");
  if (qtdProfissionais == 0) {
      printf("Nenhum profissional cadastrado.\n");
      return;
  }
  struct Profissional *p;
  for (p = profissionais; p < profissionais + qtdProfissionais; p++) {
    printf("Matricula %d | %s | Profissao %d\n", p->matricula, p->nome, p->prof_codigo);
  }
}

void mostrarClientes() {
  printf("\nClientes cadastrados:\n");
  if (qtdClientes == 0) {
      printf("Nenhum cliente cadastrado.\n");
      return;
  }
  struct Cliente *c;
  for (c = clientes; c < clientes + qtdClientes; c++) {
    printf("Codigo %d | %s | Fone %s\n", c->codigo, c->nome, c->fone);
  }
}


// --- FUNÇÕES DE CADASTRO ---

void cadastrarProfissao() {
  titulo("Cadastro de Profissao");

  if (qtdProfissoes >= MAX_PROFISSOES) {
    printf("Limite de profissoes atingido.");
    pause();
    return;
  }

  struct Profissao p;

  printf("Codigo (0 para cancelar): ");
  scanf("%d", &p.codigo);
  if (p.codigo == 0) return;

  while (encontrarProfissaoPorCodigo(p.codigo) != NULL) {
    printf("Codigo ja existente. Digite outro (0 para cancelar): ");
    scanf("%d", &p.codigo);
    if (p.codigo == 0) return;
  }
  limparEntrada();
  printf("Nome: ");
  lerLinha(p.nome, 50);
  printf("Sigla (CRM, CRO...): ");
  lerLinha(p.sigla, 10);

  profissoes[qtdProfissoes++] = p;

  printf("\nProfissao cadastrada!");
  pause();
}

void cadastrarProfissional() {
  titulo("Cadastro de Profissional");

  if (qtdProfissoes == 0) {
      printf("Erro: Nenhuma profissao cadastrada. Cadastre uma profissao primeiro.\n");
      pause();
      return;
  }

  if (qtdProfissionais >= MAX_PROFISSIONAIS) {
    printf("Limite atingido.");
    pause();
    return;
  }

  struct Profissional p;

  printf("Matricula (0 para cancelar): ");
  scanf("%d", &p.matricula);
  if (p.matricula == 0) return;

  while (encontrarProfissionalPorMatricula(p.matricula) != NULL) {
    printf("Matricula existente. Digite outra (0 para cancelar): ");
    scanf("%d", &p.matricula);
    if (p.matricula == 0) return;
  }

  printf("CPF (ex: 000.000.000-00 ou 00000000000): ");
  limparEntrada();
  lerLinha(p.cpf, 20);

  printf("Nome completo (ex: Joao da Silva): ");
  lerLinha(p.nome, 80);
  printf("Email (ex: usuario@dominio.com): ");
  lerLinha(p.email, 80);
  printf("Fone (ex: 92 3333-3333): ");
  lerLinha(p.fone, 20);

  mostrarProfissoes();
  printf("\nDigite o codigo da profissao (0 para cancelar): ");
  scanf("%d", &p.prof_codigo);
  if (p.prof_codigo == 0) return;

  while (encontrarProfissaoPorCodigo(p.prof_codigo) == NULL) {
    printf("Codigo de profissao inexistente. Digite novamente (0 para cancelar): ");
    scanf("%d", &p.prof_codigo);
    if (p.prof_codigo == 0) return;
  }

  printf("Numero RP (ex: 12345-AB): ");
  limparEntrada();
  lerLinha(p.numRP, 20);
  printf("Tipo de profissional (ex: medico, enfermeiro): ");
  lerLinha(p.tipo, 40);
  printf("Data de nascimento:\n");
  p.nascimento = lerData();

  profissionais[qtdProfissionais++] = p;

  printf("\nProfissional cadastrado!");
  pause();
}

void cadastrarCliente() {
  titulo("Cadastro de Cliente");

  if (qtdClientes >= MAX_CLIENTES) {
    printf("Limite atingido!");
    pause();
    return;
  }

  struct Cliente c;

  printf("Codigo (0 para cancelar): ");
  scanf("%d", &c.codigo);
  if (c.codigo == 0) return;

  while (encontrarClientePorCodigo(c.codigo) != NULL) {
    printf("Codigo existente. Digite outro (0 para cancelar): ");
    scanf("%d", &c.codigo);
    if (c.codigo == 0) return;
  }

  printf("Nome completo (ex: Joao da Silva): ");
  limparEntrada();
  lerLinha(c.nome, 80);
  printf("Data nascimento:\n");
  c.nascimento = lerData();
  printf("Idade: ");
  scanf("%d", &c.idade);
  printf("Email (ex: usuario@dominio.com): ");
  limparEntrada();
  lerLinha(c.email, 80);
  printf("Fone (ex: 92 3333-3333): ");
  lerLinha(c.fone, 20);
  printf("Celular (ex: 92 9 9999-9999): ");
  lerLinha(c.celular, 20);
  printf("Endereco completo (ex: Rua X, 123 - Bairro): ");
  lerLinha(c.endereco, 150);

  clientes[qtdClientes++] = c;

  printf("\nCliente cadastrado!");
  pause();
}

void cadastrarAtendimento() {
  titulo("Novo Atendimento");

  if (qtdAtendimentos >= MAX_ATENDIMENTOS) {
    printf("Limite atingido!");
    pause();
    return;
  }

  if (qtdProfissionais == 0) {
      printf("Erro: Nenhum profissional cadastrado.\n");
      pause();
      return;
  }
  if (qtdClientes == 0) {
      printf("Erro: Nenhum cliente cadastrado.\n");
      pause();
      return;
  }

  struct Atendimento a;

  printf("Numero do atendimento (0 para cancelar): ");
  scanf("%d", &a.numero);
  if (a.numero == 0) return;

  // Usando ponteiro para iterar
  struct Atendimento *atend;
  for (atend = atendimentos; atend < atendimentos + qtdAtendimentos; atend++) {
    if (atend->numero == a.numero) {
      printf("Numero existente. Digite outro (0 para cancelar): ");
      scanf("%d", &a.numero);
      if (a.numero == 0) return;
      atend = atendimentos - 1; // Reinicia o loop
    }
  }

  mostrarProfissionais();
  printf("\nDigite a matricula do profissional (0 para cancelar): ");
  scanf("%d", &a.prof_matricula);
  if (a.prof_matricula == 0) return;

  while (encontrarProfissionalPorMatricula(a.prof_matricula) == NULL) {
    printf("Matricula inexistente. Digite novamente (0 para cancelar): ");
    scanf("%d", &a.prof_matricula);
    if (a.prof_matricula == 0) return;
  }
  
  mostrarClientes();
  printf("\nDigite o codigo do cliente (0 para cancelar): ");
  scanf("%d", &a.cliente_codigo);
  if (a.cliente_codigo == 0) return;

  while (encontrarClientePorCodigo(a.cliente_codigo) == NULL) {
    printf("Codigo de cliente inexistente. Digite novamente (0 para cancelar): ");
    scanf("%d", &a.cliente_codigo);
    if (a.cliente_codigo == 0) return;
  }

  printf("Data do atendimento:\n");
  a.data = lerData();
  printf("Descricao: ");
  limparEntrada();
  lerLinha(a.descricao, 200);

  atendimentos[qtdAtendimentos++] = a;

  printf("\nAtendimento cadastrado!");
  pause();
}

// --- FUNÇÕES DE LISTAGEM (USANDO PONTEIROS) ---

void listarProfissoes() {
  titulo("Listagem de Profissoes");
  struct Profissao *p;
  for (p = profissoes; p < profissoes + qtdProfissoes; p++) {
    printf("%d - %s (%s)\n", p->codigo, p->nome, p->sigla);
  }
  if (qtdProfissoes == 0) printf("Nenhuma profissao cadastrada.\n");
  pause();
}

void listarProfissionais() {
  titulo("Listagem de Profissionais");
  struct Profissional *p;
  for (p = profissionais; p < profissionais + qtdProfissionais; p++) {
    printf("Mat: %d | Nome: %s | Profissao: %d\n", p->matricula, p->nome, p->prof_codigo);
  }
  if (qtdProfissionais == 0) printf("Nenhum profissional cadastrado.\n");
  pause();
}

void listarClientes() {
  titulo("Listagem de Clientes");
  struct Cliente *c;
  for (c = clientes; c < clientes + qtdClientes; c++) {
    printf("%d - %s | %d/%d | Fone: %s\n", c->codigo, c->nome, c->nascimento.dia, c->nascimento.mes, c->fone);
  }
  if (qtdClientes == 0) printf("Nenhum cliente cadastrado.\n");
  pause();
}

void listarAtendimentos() {
  titulo("Listagem de Atendimentos");
  struct Atendimento *a;
  for (a = atendimentos; a < atendimentos + qtdAtendimentos; a++) {
    printf("%d - Prof:%d Cliente:%d | %d/%d/%d\n", a->numero, a->prof_matricula, a->cliente_codigo, a->data.dia, a->data.mes, a->data.ano);
  }
  if (qtdAtendimentos == 0) printf("Nenhum atendimento cadastrado.\n");
  pause();
}

// --- FUNÇÕES DE RELATÓRIO (USANDO PONTEIROS) ---

void relAniversariantesProfissionais() {
  titulo("Aniversariantes Profissionais");

  int mes = lerInt("Digite o mes (1-12): ");
  while (mes < 1 || mes > 12) {
    printf("Mes invalido. Digite entre 1 e 12.\n");
    mes = lerInt("Digite o mes (1-12): ");
  }
  printf("\n");

  int encontrou = 0;
  struct Profissional *p;
  for (p = profissionais; p < profissionais + qtdProfissionais; p++) {
    if (p->nascimento.mes == mes) {
      printf("%s - %d/%d\n", p->nome, p->nascimento.dia, p->nascimento.mes);
      encontrou = 1;
    }
  }

  if (!encontrou) printf("Nenhum aniversariante encontrado neste mes.\n");
  pause();
}

void relAniversariantesClientes() {
  titulo("Aniversariantes Clientes");

  int mes = lerInt("Digite o mes (1-12): ");
  while (mes < 1 || mes > 12) {
    printf("Mes invalido. Digite entre 1 e 12.\n");
    mes = lerInt("Digite o mes (1-12): ");
  }

  int encontrou = 0;
  struct Cliente *c;
  for (c = clientes; c < clientes + qtdClientes; c++) {
    if (c->nascimento.mes == mes) {
      printf("%s - %d/%d | Fone:%s | Cel:%s | Email:%s\n", c->nome, c->nascimento.dia, c->nascimento.mes, c->fone, c->celular, c->email);
      encontrou = 1;
    }
  }

  if (!encontrou) printf("Nenhum aniversariante encontrado neste mes.\n");
  pause();
}

void relAtendimentosPorPeriodo() {
  titulo("Atendimentos por Periodo");

  struct Data ini, fim;
  printf("Data inicial:\n");
  ini = lerData();
  printf("\nData final:\n");
  fim = lerData();
  printf("\n");

  struct Atendimento *a;
  for (a = atendimentos; a < atendimentos + qtdAtendimentos; a++) {
    struct Data d = a->data;
    if (
        (d.ano > ini.ano || (d.ano == ini.ano && (d.mes > ini.mes || (d.mes == ini.mes && d.dia >= ini.dia)))) &&
        (d.ano < fim.ano || (d.ano == fim.ano && (d.mes < fim.mes || (d.mes == fim.mes && d.dia <= fim.dia)))))
    {
      printf("Num: %d | Prof:%d | Cliente:%d | %d/%d/%d\n", a->numero, a->prof_matricula, a->cliente_codigo, d.dia, d.mes, d.ano);
    }
  }
  pause();
}

void relAtendimentoPorMes() {
  titulo("Atendimento por Mes");

  int ano = lerInt("Digite o ano: ");
  int meses[13] = {0}; // Array para contar atendimentos por mês

  struct Atendimento *a;
  for (a = atendimentos; a < atendimentos + qtdAtendimentos; a++) {
    if (a->data.ano == ano) {
      meses[a->data.mes]++;
    }
  }

  printf("\nMes | Quantidade\n");
  for (int m = 1; m <= 12; m++) {
    printf("%02d | %d\n", m, meses[m]);
  }
  pause();
}

void relEstatisticaPorProfissional() {
  titulo("Estatistica por Profissional");

  int mat = lerInt("Matricula do profissional: ");
  int total = 0;

  struct Atendimento *a;
  for (a = atendimentos; a < atendimentos + qtdAtendimentos; a++) {
    if (a->prof_matricula == mat) total++;
  }

  printf("\nTotal de atendimentos: %d\n", total);
  pause();
}

// --- MENUS ---

void menuCadastros() {
    int op;
    do {
        titulo("MENU DE CADASTROS");
        printf("[1] Profissao\n");
        printf("[2] Profissional\n");
        printf("[3] Cliente\n");
        printf("[0] Voltar\n");
        op = lerInt("\nEscolha uma opcao: ");
        switch (op) {
            case 1: cadastrarProfissao(); break;
            case 2: cadastrarProfissional(); break;
            case 3: cadastrarCliente(); break;
        }
    } while (op != 0);
}

void menuListagens() {
    int op;
    do {
        titulo("MENU DE LISTAGENS");
        printf("[1] Profissoes\n");
        printf("[2] Profissionais\n");
        printf("[3] Clientes\n");
        printf("[4] Atendimentos\n");
        printf("[0] Voltar\n");
        op = lerInt("\nEscolha uma opcao: ");
        switch (op) {
            case 1: listarProfissoes(); break;
            case 2: listarProfissionais(); break;
            case 3: listarClientes(); break;
            case 4: listarAtendimentos(); break;
        }
    } while (op != 0);
}

void menuRelatorios() {
    int op;
    do {
        titulo("MENU DE RELATORIOS");
        printf("[1] Aniversariantes Profissionais\n");
        printf("[2] Aniversariantes Clientes\n");
        printf("[3] Atendimentos por Periodo\n");
        printf("[4] Atendimentos por Mes de um Ano\n");
        printf("[5] Estatistica por Profissional\n");
        printf("[0] Voltar\n");
        op = lerInt("\nEscolha uma opcao: ");
        switch (op) {
            case 1: relAniversariantesProfissionais(); break;
            case 2: relAniversariantesClientes(); break;
            case 3: relAtendimentosPorPeriodo(); break;
            case 4: relAtendimentoPorMes(); break;
            case 5: relEstatisticaPorProfissional(); break;
        }
    } while (op != 0);
}

void menuAtendimento() {
    int op;
    do {
        titulo("ATENDIMENTO");
        printf("[1] Novo Atendimento\n");
        printf("[0] Voltar\n");
        op = lerInt("\nEscolha uma opcao: ");
        if (op == 1) cadastrarAtendimento();
    } while (op != 0);
}

void menuPrincipal() {
  int op;
  do {
    titulo("SISTEMA DE SAUDE");
    printf("[1] Cadastros\n");
    printf("[2] Listagens\n");
    printf("[3] Relatorios\n");
    printf("[4] Atendimento\n");
    printf("[0] Sair\n");
    op = lerInt("\nEscolha uma opcao: ");
    switch (op) {
      case 1: menuCadastros(); break;
      case 2: menuListagens(); break;
      case 3: menuRelatorios(); break;
      case 4: menuAtendimento(); break;
    }
  } while (op != 0);
}

// --- INCREMENTAÇÃO PRINCIPAL PRO PROJECT 3, FOCO AQUI ---

void salvarDados() {
    FILE *file;

    // Salvar Profissoes
    if ((file = fopen(ARQUIVO_PROFISSOES, "wb")) != NULL) {
        fwrite(&qtdProfissoes, sizeof(int), 1, file);
        fwrite(profissoes, sizeof(struct Profissao), qtdProfissoes, file);
        fclose(file);
    }

    // Salvar Profissionais
    if ((file = fopen(ARQUIVO_PROFISSIONAIS, "wb")) != NULL) {
        fwrite(&qtdProfissionais, sizeof(int), 1, file);
        fwrite(profissionais, sizeof(struct Profissional), qtdProfissionais, file);
        fclose(file);
    }

    // Salvar Clientes
    if ((file = fopen(ARQUIVO_CLIENTES, "wb")) != NULL) {
        fwrite(&qtdClientes, sizeof(int), 1, file);
        fwrite(clientes, sizeof(struct Cliente), qtdClientes, file);
        fclose(file);
    }

    // Salvar Atendimentos
    if ((file = fopen(ARQUIVO_ATENDIMENTOS, "wb")) != NULL) {
        fwrite(&qtdAtendimentos, sizeof(int), 1, file);
        fwrite(atendimentos, sizeof(struct Atendimento), qtdAtendimentos, file);
        fclose(file);
    }
}

void carregarDados() {
    FILE *file;

    // Carregar Profissoes
    if ((file = fopen(ARQUIVO_PROFISSOES, "rb")) != NULL) {
        fread(&qtdProfissoes, sizeof(int), 1, file);
        fread(profissoes, sizeof(struct Profissao), qtdProfissoes, file);
        fclose(file);
    }

    // Carregar Profissionais
    if ((file = fopen(ARQUIVO_PROFISSIONAIS, "rb")) != NULL) {
        fread(&qtdProfissionais, sizeof(int), 1, file);
        fread(profissionais, sizeof(struct Profissional), qtdProfissionais, file);
        fclose(file);
    }

    // Carregar Clientes
    if ((file = fopen(ARQUIVO_CLIENTES, "rb")) != NULL) {
        fread(&qtdClientes, sizeof(int), 1, file);
        fread(clientes, sizeof(struct Cliente), qtdClientes, file);
        fclose(file);
    }

    // Carregar Atendimentos
    if ((file = fopen(ARQUIVO_ATENDIMENTOS, "rb")) != NULL) {
        fread(&qtdAtendimentos, sizeof(int), 1, file);
        fread(atendimentos, sizeof(struct Atendimento), qtdAtendimentos, file);
        fclose(file);
    }
}

// --- FUNÇÃO PRINCIPAL ---

int main() {
  carregarDados();
  menuPrincipal();
  salvarDados();
  printf("Dados salvos. Encerrando...\n");
  return 0;
}
