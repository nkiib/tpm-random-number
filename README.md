# TPM Random Number 

TPMを使って乱数を生成し、パスワードっぽいものを生成するコードです。コマンドライン引数に整数を与えるとその文字数のパスワードっぽいものが生成されます（上限32文字）。パスワードは生成された乱数をbase64で対応付けしてあるのでa~zの大文字小文字と+と/が生成されます。

TPMを使用した乱数なので、真性乱数のはずです。ちゃんと確認してはないですが乱数生成のための情報がTPMで枯渇すると一定時間利用できないので注意してください。

tpm2-toolsが提供するライブラリを使ってTPMにアクセスしているのでにはtpm2-toolsが必要です。

残念ながら、WSL上ではTPMへのアクセスが制限されているため、利用できませんでした（もっといい方法があるのかも）。

```sh
# Ubuntu / Debian 系
apt install libtss2-dev

# Fedora / CentOS / RHEL 系
dnf install tpm2-tts-devel
```

使用には、TPMを搭載したCPUかdTPMが必要です。またスーパーユーザ権限が必要です。`sudo`で実行してください。

# コンパイル

```
# Ubuntu / Debian 系
g++ -g src/main.cpp src/decode.cpp src/generate.cpp -o tpm-random -ltss2-sys -ltss2-tctildr

# Fedora / CentOS / REHL 系
g++ -g src/main.cpp src/decode.cpp src/generate.cpp -o tpm-random -ltss2-sys -ltss-tcto-device -ltss2-tctildr -lss2-mu
```

# 実行

```
./tpm-random
```

コマンドライン引数で桁数を指定できます（最大32）

例：

```
./tpm-random 24
```
