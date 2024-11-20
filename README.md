# TPM Random Number 

TPMを使って乱数を生成し、パスワードっぽいものを生成するコードです。コマンドライン引数に整数を与えるとその文字数のパスワードっぽいものが生成されます（上限32文字）。パスワードは生成された乱数をbase64で対応付けしてあるのでa~zの大文字小文字と+と/が生成されます。

TPMを使用した乱数なので、真性乱数のはずです。ちゃんと確認してはないですが乱数生成のための情報がTPMで枯渇すると一定時間利用できないので注意してください。

tpm2-toolsが提供するライブラリを使ってTPMにアクセスしているのでにはtpm2-toolsが必要です。

```sh
# Ubuntu / Debian 系
apt install tpm2-tools tpm2-sys

# Fedora / CentOS / RHEL 系
dnf install tpm2-tts-devel
```

使用には、TPMを搭載したCPUかdTPMが必要です。またスーパーユーザ権限が必要です。`sudo`で実行してください。