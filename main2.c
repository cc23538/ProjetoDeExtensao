#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Função para fazer o cadastro de clientes
// Definição da estrutura para o contrato de locação
typedef struct
{
char cliente_nome[100];
char tel[20];
char endereco_chacara[100];
int numero_contrato;
char data_contrato[20];
float valor_locacao;
int taxa_limpeza;
float taxa_quebra;
char assinatura[100];
} Contrato;
void criarContrato(Contrato* contrato)
{
setlocale(LC_ALL, "Portuguese");
setbuf(stdin, NULL);
printf("Nome do cliente: ");
fgets(contrato->cliente_nome, sizeof(contrato->cliente_nome), stdin);
strtok(contrato->cliente_nome, "\n");
printf("Telefone: ");
scanf("%19s[^\n]", &contrato->tel);
getchar(); // Captura o caractere de nova linha
setbuf(stdin, NULL);
printf("Endereço da chácara: ");
fgets(contrato->endereco_chacara, sizeof(contrato->endereco_chacara), stdin);
strtok(contrato->endereco_chacara, "\n");
setbuf(stdin, NULL);
printf("Número do contrato: ");
scanf("%d", &contrato->numero_contrato);
getchar(); // Captura o caractere de nova linha
setbuf(stdin, NULL);
printf("Data do contrato: ");
fgets(contrato->data_contrato, sizeof(contrato->data_contrato), stdin);
strtok(contrato->data_contrato, "\n");
setbuf(stdin, NULL);
printf("Valor da locação: ");
scanf("%f", &contrato->valor_locacao);

getchar();
setbuf(stdin, NULL);
printf("Deseja incluir a taxa de limpeza (R$200,00)? (1-Sim / 0-Não): ");
scanf("%d", &contrato->taxa_limpeza);
setbuf(stdin, NULL);
if (contrato->taxa_limpeza)
{
contrato->valor_locacao += 200.0;
}
printf("Valor da taxa de quebra (R$150,00 - R$350,00): ");
scanf("%f", &contrato->taxa_quebra);
setbuf(stdin, NULL);
printf("\n ");
printf("\t\tAssinatura Eletrônica: ");
fgets(contrato->assinatura, sizeof(contrato->assinatura), stdin);
strtok(contrato->assinatura,"\n");
printf("\t---------------------------------------------------------------------");
setbuf(stdin, NULL);
}
void salvarContrato(Contrato* contrato)
{
setlocale(LC_ALL, "Portuguese_Brasil");
FILE *arquivo = fopen("contrato_chacara.doc", "w");
if (arquivo == NULL)
{
printf("Erro ao abrir o arquivo!\n");
return;
}
fprintf(arquivo, "\t\t\t\t\tRECANTO DOS SONHOS\n");
fprintf(arquivo, "<------------------------------------------------------------------------------>\n");
fprintf(arquivo, "\n");
fprintf(arquivo, "Contrato de Locação de Chácara\n");
fprintf(arquivo, "Cliente: %s\n", contrato->cliente_nome);
fprintf(arquivo, "Telefone: %s\n", contrato->tel);
fprintf(arquivo, "Endereço da Chácara: %s\n", contrato->endereco_chacara);
fprintf(arquivo, "Número do Contrato: %d\n", contrato->numero_contrato);
fprintf(arquivo, "Data do Contrato: %s\n", contrato->data_contrato);
fprintf(arquivo, "Valor da Locação: R$%.2f\n", contrato->valor_locacao);
if (contrato->taxa_limpeza)
{
fprintf(arquivo, "Taxa de Limpeza Incluída: R$200,00\n");
}
fprintf(arquivo, "Taxa de Quebra: R$%.2f\n", contrato->taxa_quebra);
fprintf(arquivo, "\t\tassinatura: %s\n", contrato->assinatura);
fprintf(arquivo, "------------------------------------------------------\n");
fclose(arquivo);
printf("\n\nContrato gerado com sucesso e salvo em 'contrato_chacara.doc'.\n");
}

// Função para calcular o dia da semana para uma data específica
int calcularDiaSemana(int ano, int mes, int dia) {
    if (mes < 3) {
        mes += 12;
        ano--;
    }
    int K = ano % 100;
    int J = ano / 100;
    int diaDaSemana = (dia + 13 * (mes + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
    // Ajuste para domingo ser o dia 0 e sábado o dia 6
    diaDaSemana = (diaDaSemana + 6) % 7;
    return diaDaSemana;
}

void destacarDiasSelecionados(int mes, int ano, int diasAgendados[], int numDias) {
    char *nomesDosMeses[] = {"", "Janeiro", "Fevereiro", "Março",
                            "Abril", "Maio", "Junho", "Julho",
                            "Agosto", "Setembro", "Outubro", "Novembro",
                            "Dezembro"};

    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("\nCalendário para %s de %d\n", nomesDosMeses[mes], ano);
    printf("Dom\tSeg\tTer\tQua\tQui\tSex\tSáb\n");

    int primeiroDiaDoMes = calcularDiaSemana(ano, mes, 1);

    for (int i = 0; i < primeiroDiaDoMes; i++) {
        printf("\t");
    }

    for (int dia = 1; dia <= diasNoMes[mes]; dia++) {
        int agendado = 0;
        for (int i = 0; i < numDias; i++) {
            if (dia == diasAgendados[i]) {
                agendado = 1;
                break;
            }
        }
        int diaDaSemana = calcularDiaSemana(ano, mes, dia);

      if (diaDaSemana == 0) {
          printf("\033[1;91m%2d\033[0m\t", dia); // Imprime domingo em vermelho
      } else if (diaDaSemana == 6) {
          printf("\033[0;90m%2d\033[0m\t", dia); // Imprime sábado em cinza
      } else if (agendado) {
          printf("\033[1;34m%2d\033[0m\t", dia); // Imprime o dia agendado em azul
      } else {
          printf("%2d\t", dia);
      }

        if ((primeiroDiaDoMes + dia) % 7 == 0 || dia == diasNoMes[mes]) {
            printf("\n");
        }
    }
    printf("\n");
}
// Função para verificar se o ano inserido é válido
int verificarAno(int ano) {
    if (ano < 2023 || ano > 2100) {
        printf("Ano inválido. Por favor, insira um ano entre 2023 e 2100.\n");
        return 0;
    }
    return 1;
}
// Função para solicitar ao usuário os dias a serem agendados e destacá-los no calendário
void agendarNoCalendario() {
    time_t now;
    struct tm *local;
    time(&now);
    local = localtime(&now);
    int ano_atual = local->tm_year + 1900;
    int mes_atual = local->tm_mon + 1;
    int dia_atual = local->tm_mday;
    int mes, dia, ano;

    while (1) {
        printf("Digite o ano (entre 2023 e 2100): ");
        scanf("%d", &ano);

        if (verificarAno(ano)) {
            break;
        }
    }

    // Restante do código

    while (1) {
        printf("Digite o mês (entre 1 e 12): ");
        scanf("%d", &mes);

        if (mes < 1 || mes > 12) {
            printf("Mês inválido.\n");
        } else {
            break;
        }
    }

    // Solicita ao usuário os dias a serem agendados
    printf("Quantos dias você deseja agendar? ");
    int numDias;
    scanf("%d", &numDias);

    int diasAgendados[numDias];
    for (int i = 0; i < numDias; i++) {
        printf("Digite o dia a ser agendado (entre 1 e 31): ");
        scanf("%d", &diasAgendados[i]);
    }

    // Verificação para garantir que o usuário não agende em datas passadas
    if (ano == ano_atual && mes < mes_atual) {
        printf("Não é possível agendar para uma data que já passou.\n");
        return;
    }

    // Mostra o calendário com os dias agendados em azul
    printf("\nCalendário com dias agendados:\n");
    printf("=============================================\n");
    destacarDiasSelecionados(mes, ano, diasAgendados, numDias);
}



void calendario() {
    int ano, mes;
    while (1) {
        printf("Digite o ano (entre 2000 e 2100): ");
        scanf("%d", &ano);

        if (ano >= 2000 && ano <= 2100) {
            break; // Sai do loop se o ano for válido.
        } else {
            printf("Ano inválido.\n");
        }
    }

    while (1) {
        printf("Digite o mês (entre 1 e 12): ");
        scanf("%d", &mes);

        if (mes >= 1 && mes <= 12) {
            break; // Sai do loop se o Mês for válido.
        } else {
            printf("Mês inválido.\n");
        }
    }

    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) {
        diasNoMes[2] = 29; // Fevereiro tem 29 dias em um ano bissexto
    }

    char *nomesDosMeses[] = {"",        "Janeiro",  "Fevereiro", "Março",
                            "Abril",   "Maio",     "Junho",     "Julho",
                            "Agosto",  "Setembro", "Outubro",   "Novembro",
                            "Dezembro"};

    printf("\nCalendário para %s de %d\n", nomesDosMeses[mes], ano);
    printf("Dom\tSeg\tTer\tQua\tQui\tSex\tSáb\n");

    int primeiroDiaDoMes = calcularDiaSemana(ano, mes, 1);

    for (int i = 0; i < primeiroDiaDoMes; i++) {
        printf("\t");
    }

    // Gerar 3 dias aleatórios
    int diasRealcados[5];
    for (int i = 0; i < 5; i++) {
        diasRealcados[i] = rand() % diasNoMes[mes] + 1;
    }

    for (int dia = 1; dia <= diasNoMes[mes]; dia++) {
        int realcado = 0;
        for (int i = 0; i < 5; i++) {
            if (dia == diasRealcados[i]) {
                realcado = 1;
                break;
            }
        }
        int diaDaSemana = calcularDiaSemana(ano, mes, dia);

      if (realcado) {
          printf("\033[1;34m%2d\033[0m\t", dia); // Imprime o dia realçado em azul
      } else if (diaDaSemana == 0) {
          printf("\033[1;31m%2d\033[0m\t", dia); // Imprime domingo em vermelho
      } else if (diaDaSemana == 6) {
          printf("\033[1;90m%2d\033[0m\t", dia); // Imprime sábado em cinza
      } else {
          printf("%2d\t", dia);
      }

        if ((primeiroDiaDoMes + dia) % 7 == 0 || dia == diasNoMes[mes]) {
            printf("\n");
        }
    }
    printf("\n");
}


// função cadastro de chácaras
// Estrutura para armazenar os detalhes das chácaras
typedef struct {
  char nome[50];
  char detalhes[11][50];
} Chacara;

// Função para imprimir os detalhes de cada chácara
void imprimirDetalhesChacara(Chacara chacara) {
  printf("\033[0;31mNOME DA CHÁCARA: %s\033[0m\n", chacara.nome);
  printf("Detalhes:\n");
  for (int i = 0; i < 11; i++) {
    printf("- %s\n", chacara.detalhes[i]);
  }
  printf("\n");
}

// Função de cadastro de chácaras
void cadastroChacaras(Chacara *chacarasDisponiveis, int numChacaras) {
  printf("\033[0;34m********* Bem-vindo ao Cadastro de Chácaras *********\n\n\033[0m");

  for (int j = 0; j < numChacaras; j++) {
    Chacara novaChacara;
    printf("Digite o nome da chácara %d: ", j + 1);
    fgets(novaChacara.nome, 50, stdin);

    printf("Digite os detalhes da chácara:\n");
    for (int i = 0; i < 11; i++) {
      printf("Detalhe %d: ", i + 1);
      fgets(novaChacara.detalhes[i], 50, stdin);
    }

    chacarasDisponiveis[j] = novaChacara;
  }
}

// Função para exibir as chácaras cadastradas
void exibirChacarasCadastradas(Chacara *chacarasDisponiveis, int numChacaras) {
  printf("\033[0;34m********* Chácaras Cadastradas *********\n\n\033[0m");

  for (int i = 0; i < numChacaras; i++) {
    imprimirDetalhesChacara(chacarasDisponiveis[i]);
  }
}

// Definindo a estrutura para armazenar informa��es do usu�rio
struct Usuario {
  char nome[50];
  char senha[20];
};
// Fun��o para verificar o login
int verificarLogin(struct Usuario usuarios[], int numUsuarios, char nome[],
                   char senha[]) {
  for (int i = 0; i < numUsuarios; i++) {
    if (strcmp(usuarios[i].nome, nome) == 0 &&
        strcmp(usuarios[i].senha, senha) == 0) {
      return i; // Retorna o �ndice do usu�rio se o login for bem-sucedido
    }
  }
  return -1; // Retorna -1 se o login falhar
}

int main() {
  setlocale(LC_ALL, "Portuguese");
  // Defina os dados do usu�rio.
  struct Usuario usuarios[2];
  strcpy(usuarios[0].nome, "usuario1");
  strcpy(usuarios[0].senha, "senha1");
  strcpy(usuarios[1].nome, "usuario2");
  strcpy(usuarios[1].senha, "senha2");

  int numUsuarios = 2;

  char nome[50];
  char senha[20];

  int opcao;
  int usuarioLogado = -1;
  
  //variaves de criação de chacara
  int numChacaras = 3; // Define o número de chácaras disponíveis
  Chacara chacarasDisponiveis[numChacaras];

  while (1) { // Loop principal
    if (usuarioLogado == -1) {
      printf("Bem-vindo!\n");
      printf("Nome de usu�rio: ");
      scanf("%s", nome);
      printf("Senha: ");
      scanf("%s", senha);

      usuarioLogado = verificarLogin(usuarios, numUsuarios, nome, senha);

      if (usuarioLogado == -1) {
        printf("Login falhou. Tente novamente.\n");
      }
    } else {
      printf("\n*** Menu Principal ***\n");
      printf("1. Cadastro de Clientes\n");
      printf("2. Cadastro de Chácaras\n");
      printf("3. Visualizar Chácaras Disponíveis\n"); 
      printf("4. Agendar Visitas\n");
      printf("5. Agendar Diárias\n");
      printf("6. Contrato\n");
      printf("7. Calendário\n");
      printf("8. Sair\n");
      printf("Escolha uma opção: ");
      scanf("%d", &opcao);

      switch (opcao) {
      case 1:
        printf("Voc� selecionou Cadastro de Clientes.\n");
        // Coloque a l�gica do cadastro de clientes aqui
        printf("\n--------------------------------");
        printf("RECANTOS DOS SONHOS");
        printf("-------------------------------------------\n");
        Contrato contrato;
        criarContrato(&contrato);
        salvarContrato(&contrato);

        break;
      case 2:
        printf("Voc� selecionou Cadastro de Chácaras.\n");
        // Coloque a l�gica do Cadastro de Chácaras
        //cadastroChacaras();
        
        // Cadastro das chácaras
        cadastroChacaras(chacarasDisponiveis, numChacaras);
        
        break;
      case 3:
        printf("Você selecionou Visualizar Chácaras Disponíveis.\n");
        exibirChacarasCadastradas(chacarasDisponiveis, numChacaras);
        break;
      case 4:
        printf("Voc� selecionou Agenda de Visitas.\n");
        // Coloque a l�gica da agenda de visitas aqui
        printf(
            "Escolha o mês e o ano, para visualizar as datas disponíves\n\n");
        calendario();
        int dia, mes, ano;
        int hora = 0, min = 0;
        char opcao;

        printf("\nQue dia você deseja agendar uma visita? ");
        scanf("%d %d %d", &dia, &mes, &ano);
        printf("\n%d/%d/%d", dia, mes, ano);
        printf("\nConfirma essa data? (S/N) ");
        scanf("%s", &opcao);
        if (opcao == 'S' || opcao == 's') {
          printf("Opção válida\n");

        } else if ((opcao == 'N' || opcao == 'n')) {
          printf("Opção inválida\n");
        }
        printf("\nQue hora você deseja agendar o horário? ");
        scanf("\n%d", &hora);
        scanf("\n%d", &min);

        printf("%d:%d", hora, min);
        printf("\nConfirma esse horário? (S/N)");
        scanf("%s", &opcao);
        if (opcao == 'S' || opcao == 's') {
          printf("Opção válida\n");

        } else if ((opcao == 'N' || opcao == 'n')) {
          printf("Opção inválida\n");
        }

        break;
      case 5:
        // Coloque a l�gica da agenda de di�rias aqui
        printf("Você selecionou Agendar Diárias.\n\n");
        agendarNoCalendario();
        printf("\n\n");
        break;
      case 6:
        printf("Voc� selecionou Contrato.\n");
        // Coloque a l�gica do contrato aqui
        // Vari�veis para informa��es do contrato
        char nomeCliente[100];
        float valorLocacao = 0.0;
        int telefoneCliente;
        int dddTelefone;
        int diaEvento;
        int mesEvento;
        int anoEvento;
        int anoBissexto;
        int quantidadeDias;
        int maxDiasFevereiro = 28;
        int diaSemana[31];
        int i;

        // SOLICITAR INFORMA��ES PARA O CONTRATO
        printf("\nPREENCHA AS INFORMA��ES NECESS�RIAS PARA IMPRESS�O!\n");
        printf("\nInforme o nome do cliente: ");
        scanf("%99[^\n]", nomeCliente);

        // 1. DDD TELEFONE DO CLIENTE:
        printf("\nInforme o ddd do telefone do cliente: ");
        scanf("%d", &dddTelefone);

        // 1.1 Verifica��o ddd telefone do cliente
        while (dddTelefone < 11 || dddTelefone > 99) {
          printf("\nERRO! o ddd digitado � inv�lido!");
          printf("\nDigite um ddd v�lido: ");
          scanf("%d", &dddTelefone);
        }

        // 2. TELEFONE DO CLIENTE:
        printf("\nInforme o telefone do cliente: ");
        scanf("%d", &telefoneCliente);

        // 2.1 Verifica��o Telefone do cliente
        while (telefoneCliente < 0) {
          printf("\nERRO! o valor digitado � inv�lido!");
          printf("\nDigite um telefone v�lido: ");
          scanf("%d", &telefoneCliente);
        }

        // 3. ANO DA LOCA��O:
        printf("\nInforme o ano do evento/loca��o: ");
        scanf("%d", &anoEvento);

        // 3.1 Verifica��o ano da loca��o
        while (anoEvento < 0 || anoEvento < 2023) {
          printf("\nERRO! Ano do evento digitado inv�lido!");
          printf("\nDigite novamente o ano do evento: ");
          scanf("%d", &anoEvento);
        }

        // 3. M�S DA LOCA��O:
        printf("\nInforme o m�s do evento/loca��o: ");
        scanf("%d", &mesEvento);

        // 3.1 Verifica��o m�s da loca��o
        while (mesEvento <= 0 || mesEvento > 12) {
          printf("\nERRO! M�s do evento digitado inv�lido!");
          printf("\nDigite novamente o m�s do evento: ");
          scanf("%d", &mesEvento);
        }

        // 4. DIA DA LOCA��O:
        printf("\nInforme o dia do evento/locacao: ");
        scanf("%d", &diaEvento);

        // 4.1 Verifica��o dia da loca��o (Meses com 31 dias)
        if (mesEvento == 1 || mesEvento == 3 || mesEvento == 5 ||
            mesEvento == 7 || mesEvento == 8 || mesEvento == 10 ||
            mesEvento == 12) {
          while (diaEvento < 0 || diaEvento > 31) {
            printf("\nERRO! Dia do evento digitado inv�lido!");
            printf("\nDigite novamente dia do evento (1 - 31): ");
            scanf("%d", &diaEvento);
          }
        }

        // 4.2 Verifica��o dia da loca��o (M�s com 28 ou 29 dias)
        // 4.3 verificar se o ano � bissexto ou n�o
        for (int anoBissexto = 2024; anoBissexto <= anoEvento;
             anoBissexto += 4) {
          maxDiasFevereiro = (anoBissexto % 4 == 0 && (anoBissexto % 100 != 0 ||
                                                       anoBissexto % 400 == 0))
                                 ? 29
                                 : 28;
        }

        if (mesEvento == 2) {
          while (diaEvento < 1 || diaEvento > maxDiasFevereiro) {
            printf("\nERRO! Dia do evento digitado inv�lido para fevereiro em "
                   "um ano %s bissexto!\n",
                   (maxDiasFevereiro == 29) ? "�" : "n�o �");
            printf("Digite novamente o dia do evento (1 - %d): ",
                   maxDiasFevereiro);
            scanf("%d", &diaEvento);
          }
        }

        // 4.4 Verificando dia da loca��o (M�s com 30 dias)
        else if (mesEvento == 4 || mesEvento == 6 || mesEvento == 9 ||
                 mesEvento == 11) {
          while (diaEvento < 0 || diaEvento > 30) {
            printf("\nERRO! Dia do evento digitado inv�lido!");
            printf("\nDigite novamente dia do evento (1 - 30): ");
            scanf("%d", &diaEvento);
          }
        }

        // 5. QUANTIDADE DE DIAS LOCA��O
        printf("\nInforme a quantidade de dias de locacao: ");
        scanf("%d", &quantidadeDias);

        // 5.1 Verifica��o da quantidade de dias
        while (quantidadeDias < 1 || quantidadeDias > 31) {
          printf("\nERRO! O valor digitado � inv�lido ou excede o limite "
                 "m�ximo de 31 dias!");
          printf("\nDigite a quantidade de dias novamente: ");
          scanf("%d", &quantidadeDias);
        }

        // 6. DIAS DA LOCA��O
        for (i = 1; i <= quantidadeDias; i++) {
          printf("\nInforme o %d� dia da semana da loca��o \n1 - Segunda \n2 - "
                 "Ter�a \n3 - Quarta \n4 - Quinta \n5 - Sexta \n6 - S�bado \n7 "
                 "- Domingo: ",
                 i);
          scanf("%d", &diaSemana[i - 1]);
        }

        // 7. VALOR DA LOCA��O (QUANTIDADE DE DIAS E DIAS DE SEMANA)
        for (i = 0; i < quantidadeDias; i++) {
          switch (diaSemana[i]) {
          case 1: // Segunda
          case 2: // Ter�a
          case 3: // Quarta
          case 4: // Quinta
          case 5: // Sexta
            valorLocacao += 500.0;
            break;
          case 6: // S�bado
          case 7: // Domingo
            valorLocacao += 550.0;
            break;
          default:
            printf("\nERRO! Dia da semana inv�lido! O dia %d n�o ser� "
                   "considerado.\n",
                   diaSemana[i]);
            break;
          }
        }

        // IMPRIMIR DADOS NA TELA DO SISTEMA (obs: impress�o final ser� feita em
        // txt)
        printf("\n\n\nCONTRATO DE LOCA��O RECANTO DOS SONHOS\n\n");
        printf("Valor da diaria: Segunda � Sexta: R$500,00 - Sabado � Domingo: "
               "R$550,00\n");
        printf("Telefone: (19) 99580-8156\n");
        printf("Endereco: Rua dois, N� 1071 - jardim Itagua�u 2, Campinas - "
               "SP, CEP 13053-788, Brasil\n\n");
        printf("Locatario: %s\n", nomeCliente);
        printf("Quantidade de Dias de Locacao: %d\n", quantidadeDias);
        printf("Valor total da Loca��o: R$%.2f\n", valorLocacao);
        printf("Telefone do Locatario: (%d)%d\n", dddTelefone, telefoneCliente);
        printf("Data do Evento/Locacao: %d/%d/%d\n\n", diaEvento, mesEvento,
               anoEvento);
        printf("Assinatura do Locatario: ____________\n");
        printf("Data de hoje: __ /__ /_____\n");
        printf("Campinas, SP\n\n");
        printf("Assinatura do Locador: ____________\n");
        break;
      case 7:
        printf("Voc� selecionou Calendario.\n\n");
        // Coloque a l�gica do calendario aqui
        calendario();
        break;

      case 8:
        printf("Saindo...\n");
        exit(0); // Saia do programa
      default:
        printf("Op��o inv�lida. Tente novamente.\n");
      }
    }
  }

  return 0;
}
