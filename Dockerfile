FROM yastdevel/cpp:sle12-sp4

RUN zypper --gpg-auto-import-keys --non-interactive in --no-recommends \
  libcurl-devel
COPY . /usr/src/app

