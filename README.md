# BUD-e
The BUD-e Discord Bot, rewrote in C++!
Updates will be made frequently.

BUD-e' is automated via Jenkins and will update locally every git push, however, this does not update the bot whilst running.
BUD-e will update on discord when he's flagged to do so. BUD-e has two versions:

- Experimental
- Stable

These are different bots. The Experimental version is a bot that is only ever online when running locally. Stable is the official "BUD-e" bot.
Experimental also serves as a testing ground for D++ contributions.

## Libraries

- D++ (Create a `libs` folder, do `cd libs`, then clone `git clone https://github.com/brainboxdotcc/DPP.git`)
- `libmysqlclient-dev` (If on Debian 9+, it's `default-libmysqlclient-dev`).
- `libfmt-dev`