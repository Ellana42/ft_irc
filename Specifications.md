# ft_IRC Server Specifications

This server will use:

* TCP/IP v4
* Irssi client

I/O operations :

* non blocking
* only one poll() (or equivalent)
* all read/recv - write/send must be used with poll

## Usage

The server should be launched with:

```shell
/ircserv <port> <password>
```

### Server Commands

| Command                                  | Description                                                                                                                                                                                                                                |
|------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `HELP`                                   | Requests the server to display the help file.                                                                                                                                                                                              |
| `USER <user> <mode> <unused> <realname>` | This command is used at the beginning of a connection to specify the username, hostname, real name and initial user modes of the connecting client.                                                                                        |
| `JOIN <channels>`                        | Makes the client join the channels in the comma-separated list `<channels>`. If the channel(s) do not exist then they will be created.                                                                                                     |
| `KICK <channel> <client> :[<message>]`   | Forcibly removes `<client>` from `<channel>`. This command may only be issued by channel operators.                                                                                                                                        |
| `LIST`                                   | Lists all channels on the server.                                                                                                                                                                                                          |
| `NAMES [<channels>]`                     | Returns a list of who is on the comma-separated list of `<channels>`, by channel name. If `<channels>` is omitted, all users are shown, grouped by channel name with all users who are not on a channel being shown as part of channel "*" |
| `NICK <nickname>`                        | Allows a client to change their IRC nickname.                                                                                                                                                                                              |
| `PART <channels> [<message>]`            | Causes a user to leave the channels in the comma-separated list `<channels>`.                                                                                                                                                              |
| `PRIVMSG <msgtarget> :<message>`         | Sends `<message>` to `<msgtarget>`, which is usually a user or channel.                                                                                                                                                                    |
| `QUIT [<message>]`                       | Disconnects the user from the server.                                                                                                                                                                                                      |
| `USERS`                                  | Returns a list of users and information about those users in a format similar to the UNIX commands who, rusers and finger.                                                                                                                 |
| `VERSION`                                | Returns the version of the current server.                                                                                                                                                                                                 |
| `WHO [<name>]`                           | Returns a list of users who match `<name>`.                                                                                                                                                                                                |
