FROM archlinux

RUN pacman -Sy --noconfirm git neovim make gcc zsh curl nasm xxd

# TODO ADD multilib-dev support

RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

ENTRYPOINT [ "zsh" ]
