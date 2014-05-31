# weechat-recommand

A WeeChat command that resends the automatic command(s) (`irc.server.xxxxxx.command`) for the current server if desired.

## What?

A certain unnamed network keeps having issues with their services and I'm tired of manually retyping NickServ identification every time it happens. Instead of just reconnecting, writing a plugin is obviously the most sensible solution to this issue. Enter `/recommand`!

## Usage

    > /set irc.server.example.command
    ...
    irc.server.example.command = "/msg nickserv identify hunter2"
    ...

    > /recommand
    MSG(nickserv): identify *******

## Build and installation

    make

    # Install system-wide
    make install

    # Install to your ~/.weechat
    make homeinstall

## License

GPLv3 because WeeChat's license doesn't give me much choice. See `LICENSE`.
