FROM yastdevel/cpp:sle15
RUN zypper --gpg-auto-import-keys --non-interactive in --no-recommends \
  libcurl-devel
COPY . /usr/src/app

