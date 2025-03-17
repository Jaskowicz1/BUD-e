# BUD-e
The BUD-e Discord Bot, rewrote in C++!
Updates will be made frequently.

BUD-e is automated via GitHub Actions. All your commits should be pushed to the "dev" branch via a PR. "dev" branch will auto-update the "BUD-e Experimental" bot.
Once happy with changes in "dev", merge commits to "main". This wll auto-update the main BUD-e bot.

## Libraries

- D++ (Create a `libs` folder, do `cd libs`, then clone `git clone https://github.com/brainboxdotcc/DPP.git`. This allows easy change between dev branches of D++)
- `libmysqlclient-dev` (If on Debian 9+, it's `default-libmysqlclient-dev`).
- `libfmt-dev`
