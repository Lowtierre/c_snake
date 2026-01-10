# c_snake 🐍 — Snake in C (console)

Un piccolo **Snake in C** che gira in console e si controlla con le **frecce**.
Il gioco disegna una griglia testuale, mostra la lunghezza del serpente e genera un “frutto” casuale: quando lo prendi, il serpente cresce.

> Nota compatibilità: molte implementazioni “console” di Snake in C usano `conio.h` (`_kbhit()`, `_getch()`) e comandi come `cls` per pulire lo schermo.  
> Se il tuo `snake.c` usa queste funzioni, la compilazione **out-of-the-box** è pensata per **Windows / MinGW**.  
> Se vuoi che questo README sia *perfettamente* allineato al tuo file riga-per-riga, ricarica `snake.c` (il file allegato in precedenza qui risulta scaduto).

---

## Contenuto della repository

Struttura minima consigliata:

```
c_snake/
├─ snake.c
└─ README.md
```

---

## Requisiti

### Windows (consigliato)
- Un compilatore C (**GCC MinGW-w64** consigliato)
- Un terminale (Windows Terminal / MSYS2 / PowerShell)

### Linux / macOS
- GCC o Clang installati
- ⚠️ Se il tuo `snake.c` usa `conio.h`, **non compila** su Linux/macOS senza adattamenti (input non bloccante e clear schermo).

---

## Scaricare la repo

### Opzione A — Clona con Git
```bash
git clone https://github.com/<TUO-USERNAME>/c_snake.git
cd c_snake
```

### Opzione B — Scarica ZIP
1. Apri la repo su GitHub
2. **Code → Download ZIP**
3. Estrai la cartella e aprila nel terminale

---

## Compilare `snake.c`

### ✅ Windows (MinGW-w64 / MSYS2)

Verifica il compilatore:
```bash
gcc --version
```

Compilazione consigliata:
```bash
gcc -std=c11 -Wall -Wextra -O2 snake.c -o snake.exe
```

Compilazione “base”:
```bash
gcc snake.c -o snake.exe
```

Avvio:
```bash
./snake.exe
```

> In `cmd` puoi anche eseguire: `snake.exe`

---

### ⚠️ Linux / macOS

Se il tuo file **NON** usa `conio.h`, prova:
```bash
gcc -std=c11 -Wall -Wextra -O2 snake.c -o snake
./snake
```

Se invece **usa** `conio.h` / `_kbhit()` / `_getch()`:
- non è disponibile su Linux/macOS
- serve sostituire l’input con `termios` (POSIX) e la pulizia schermo con `clear` o escape ANSI

👉 Se vuoi, posso convertire `snake.c` in una versione **cross-platform** (senza librerie esterne) mantenendo lo stesso gameplay.

---

## Controlli di gioco

- **Frecce direzionali**: muovi il serpente
- In molte versioni non puoi invertire direzione istantaneamente (su↔giù, sinistra↔destra) quando il serpente ha lunghezza > 1

---

## Troubleshooting

### “gcc: command not found”
Il compilatore non è installato o non è nel PATH.
- **macOS**:
  ```bash
  xcode-select --install
  ```
- **Ubuntu/Debian**:
  ```bash
  sudo apt update && sudo apt install build-essential
  ```
- **Fedora**:
  ```bash
  sudo dnf install gcc
  ```
- **Windows**: installa **MSYS2** e il toolchain MinGW-w64.

### Output “sballato” in console (cursor / caratteri)
Alcuni programmi usano escape ANSI per posizionare il cursore. Usa preferibilmente:
- **Windows Terminal** (consigliato)
- terminale MSYS2 aggiornato

---

## Licenza

Aggiungi una licenza (es. MIT) oppure rimuovi questa sezione.
