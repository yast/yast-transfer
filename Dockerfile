FROM registry.opensuse.org/yast/sle-15/sp2/containers/yast-cpp
RUN zypper --gpg-auto-import-keys --non-interactive in --no-recommends \
  libcurl-devel
COPY . /usr/src/app

