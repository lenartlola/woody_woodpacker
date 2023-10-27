FROM archlinux

RUN pacman -Sy --noconfirm git neovim make gcc zsh curl nasm xxd

# TODO ADD multilib-dev support

# [multilib-testing]
# Include = /etc/pacman.d/mirrorlist

# [multilib]
# Include = /etc/pacman.d/mirrorlist

COPY ./pacman.conf /etc/pacman.conf

RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

ENTRYPOINT [ "zsh" ]
