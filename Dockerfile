FROM archlinux

RUN pacman -Sy --noconfirm git neovim make gcc zsh curl nasm

RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

RUN curl -sLf https://spacevim.org/install.sh | bash

COPY . woody_woodpacker

ENTRYPOINT [ "zsh" ]
