FROM archlinux

RUN pacman -Sy --noconfirm git neovim make gcc zsh curl nasm

RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

COPY . woody_woodpacker

ENTRYPOINT [ "zsh" ]
