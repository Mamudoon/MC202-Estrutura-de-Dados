#!/usr/bin/env python3
"""
Gerador de entradas de estresse para o exercicio "Indexador de documentos" (AVL).

Gera 3 arquivos:
  teste_insercao.in   -> foca em 'i' (insercoes em ordem crescente, decrescente,
                         zigue-zague e aleatoria + muitas duplicatas ignoradas)
  teste_atualizacao.in -> monta arvore grande e faz muitos 'a' (existentes e inexistentes)
  teste_busca.in      -> monta arvore grande e faz muitos 'b' (existentes e inexistentes)

Uso:
  python3 gera_entradas.py            # tamanho padrao
  python3 gera_entradas.py 1000000    # N documentos personalizado

Depois:
  time ./seu_programa < teste_insercao.in > /dev/null
"""
import random
import sys

N = int(sys.argv[1]) if len(sys.argv) > 1 else 500_000   # tamanho da arvore
OPS = N                                                     # nº de operacoes do foco

VIS = ["restrito", "interno", "publico", "bloqueado"]
EST = ["atualizado", "desatualizado", "obsoleto"]

random.seed(202)


def doc():
    return f"{random.choice(VIS)} {random.choice(EST)}"


def ids_variados(n):
    """Mistura padroes que degeneram arvores mal balanceadas.
    IDs grandes (cabem em long de 64 bits) para pegar quem usa int."""
    base = 3_000_000_000  # > INT_MAX de proposito
    q = n // 4
    crescente = [base + 2 * k for k in range(q)]                 # rotacoes a esquerda
    decrescente = [base - 2 * k - 2 for k in range(q)]           # rotacoes a direita
    # zigue-zague: forca rotacoes duplas (LR / RL)
    zz = []
    lo, hi = base + 10 * n, base + 20 * n
    while len(zz) < q:
        zz.append(lo); lo += 1
        zz.append(hi); hi -= 1
    zz = zz[:q]
    resto = n - 3 * q
    aleat = random.sample(range(base + 30 * n, base + 60 * n), resto)
    return crescente + decrescente + zz + aleat


def escreve(nome, linhas):
    with open(nome, "w") as f:
        f.write("\n".join(linhas))
        f.write("\n")
    print(f"{nome}: {len(linhas)} linhas")


# ---------------------------------------------------------------- 1) insercao
def gera_insercao():
    ids = ids_variados(N)
    linhas = ["l", "t"]                          # arvore vazia
    for x in ids:
        linhas.append(f"i {x} {doc()}")
    # duplicatas (devem ser ignoradas) - tambem percorrem a altura toda
    for x in random.sample(ids, N // 2):
        linhas.append(f"i {x} {doc()}")
    linhas += ["t", "l", "f"]
    escreve("teste_insercao.in", linhas)


# ------------------------------------------------------------- 2) atualizacao
def gera_atualizacao():
    ids = sorted(ids_variados(N))
    linhas = [f"i {x} {doc()}" for x in ids]     # insercao crescente: pior caso p/ BST
    linhas.append("t")
    folhas_fundas = ids[::2]                     # boa parte vira folha
    for k in range(OPS):
        r = random.random()
        if r < 0.70:
            x = random.choice(folhas_fundas)     # existe
        elif r < 0.85:
            x = ids[-1] + 1 + k                  # nao existe (maior que todos)
        else:
            x = ids[0] - 1 - k                   # nao existe (menor que todos)
        linhas.append(f"a {x} {doc()}")
        if k % 50_000 == 0:
            linhas.append("t")                   # confere contadores no meio
    linhas += ["t", "f"]
    escreve("teste_atualizacao.in", linhas)


# ------------------------------------------------------------------ 3) busca
def gera_busca():
    ids = sorted(ids_variados(N))
    linhas = [f"i {x} {doc()}" for x in reversed(ids)]  # insercao decrescente
    for k in range(OPS):
        r = random.random()
        if r < 0.6:
            x = random.choice(ids)                       # existe
        elif r < 0.8:
            # nao existe, mas "entre" dois ids -> desce ate uma folha
            i = random.randrange(len(ids) - 1)
            x = ids[i] + 1 if ids[i] + 1 != ids[i + 1] else ids[-1] + 7
        else:
            x = random.choice([ids[0], ids[-1], ids[0] - 5, ids[-1] + 5])  # extremos
        linhas.append(f"b {x}")
    linhas += ["t", "f"]
    escreve("teste_busca.in", linhas)


if __name__ == "__main__":
    gera_insercao()
    gera_atualizacao()
    gera_busca()