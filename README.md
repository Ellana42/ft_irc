# ft_irc

A small IRC server made in C++.

## Usage

Clone this repository and `cd` into it. To build, use

```
make
```

To launch the server:

```
./ircserv <port> <password>
```

### Connecting to the Server Using IRSSI

This project was developed for the IRSSI client. After launching `irssi`, run the following command:

```
/connect localhost <server_port> <server_password>
```

### Connecting to the Server Using NetCat

Alternatively, connect to the server using `nc`, `netcat` or `ncat`, whichever one has the `-C` or `--crlf` options to enable CRLF for EOL sequence.

```
nc -C localhost <server_port>
```

Then, you can input your IRC commands. To properly register on the server, use the following commands:

```
PASS <server_password>
USER <user> <mode(unused)> <host(unused)> <realname>
NICK <nickname>
```

## Implemented Commands

- `ADMIN`: Displays information about the administrator of the server.
- `INFO`: Displays information about the server.
- `INVITE <nickname> <channel_name>`: Invites a user to a channel.
- `JOIN <channel_name>`: Joins an existing channel or creates one. If `*` is specified as the channel name, removes the user from all channels.
- `KICK <nickname> <channel_name>`: Kicks a user from a channel (this is a channel operator command)
- `LIST`: Lists all channels on the server.
- `MODE <channel_name> <mode(s)>`: Sets/removes channel modes. Implemented channel modes:
    - `i`: set/remove invite-only mode.
    - `k`: set/remove the channel key (password)
    - `l`: set/remove a channel's user limit
    - `o`: give/take channel operator privileges
    - `t`: set/remove the restrictions of the TOPIC command to channel operators
- `NAMES`: lists all of the nicknames on the server.
- `NICK <nickname>`: sets the user's nickname.
- `PART <channel_name> <message>`: removes user from channel(s) and notifies the other users in the channel.
- `PASS <password>`: Used for registration to the server. The client must supply the server password as part of the registration process.
- `PING`: Used to test the presence of an active client.
- `PONG`: Used to reply to a `PING` message.
- `PRIVMSG <nickname_or_channel_name> <message>`: sends a message to the specified user or channel.
- `QUIT <message>`: Removes the user from the server and notifies other users in the channels the quitting user was in.
- `SUMMON`: Not implemented.
- `TOPIC <channel_name> <message>`: sets message as the channel topic.
- `USER <user> <mode(unused)> <host(unused)> <realname>`: sets a new user's information during registration.
- `USERS`: Not implemented.
- `VERSION`: Displays the server version.

