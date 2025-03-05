# Roguelike

## Description

The best game of 2025. Developed by students of matmech: 

[Smola Artem](https://github.com/artem-smola),
[Kozhukov Ivan](https://github.com/Oddin60F),
[Rechkin Vadim](https://github.com/VadosikRRR)

### How to run (ONLY LINUX)

#### 1. Clone the repository into a convenient folder and go to the `Game` folder

```bash
git clone git@github.com:VadosikRRR/Game.git
cd Game
```

#### 2. Create the `build` folder, and in it `Desktop-Debug` and go to the latest

```bash
mkdir build
cd build
mkdir Desktop-Debug
cd Desktop-Debug
```

#### 3. Next is the compilation

```bash
cmake ../..
```

```bash
make
```

#### 4. Launch `Roguelike`

```bash
./RogueLike
```