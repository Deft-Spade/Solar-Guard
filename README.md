# Solar Guard
A [homebrew](https://en.wikipedia.org/wiki/Homebrew_(video_games)) [Game Boy Advance](https://en.wikipedia.org/wiki/Game_Boy_Advance) game made for [GBA Jam 2021](https://itch.io/jam/gbajam21).

The game is intended to be a space shooter where you complete various missions in the solar system.

This game is currently under active development (i.e. any build thus far can be considered a development version).

# Acknowledgements/Attributions

## Programming
- This game was made using [GValiente](https://github.com/GValiente)'s [Butano](https://github.com/GValiente/butano) engine (and uses a font from the Butano examples).

	> Butano is a modern C++ high level engine for the [Game Boy Advance](https://en.wikipedia.org/wiki/Game_Boy_Advance).
    
## Art
- [***Solar System***](https://opengameart.org/sites/default/files/space.png) by [ShinyOgre](https://opengameart.org/users/shinyogre) licensed [**CC-BY-SA 3.0**](https://creativecommons.org/licenses/by-sa/3.0/): [https://opengameart.org/content/solar-system](https://opengameart.org/content/solar-system)

- [***Planet Orbit Background***](https://opengameart.org/content/planet-orbit-background) by [ArthCarvalho](https://opengameart.org/users/arthcarvalho) licensed [**OGA-BY 3.0**](https://static.opengameart.org/OGA-BY-3.0.txt): [https://opengameart.org/content/planet-orbit-background](https://opengameart.org/content/planet-orbit-background)

- [***Space Background***](https://opengameart.org/content/space-background-1) by [Westbeam](https://opengameart.org/users/westbeam) licensed [**CC0**](https://creativecommons.org/publicdomain/zero/1.0/): [https://opengameart.org/content/space-background-1](https://opengameart.org/content/space-background-1)

- [***Space Ships***](https://opengameart.org/content/space-ships-0) by [Eikester](https://opengameart.org/users/eikester) licensed [**CC-BY 3.0**](https://creativecommons.org/licenses/by/3.0/): [https://opengameart.org/content/space-ships-0](https://opengameart.org/content/space-ships-0)

- [***Space Ships***](https://opengameart.org/content/space-ships-1) by [nareiK](https://opengameart.org/users/nareik) licensed [**CC-BY 3.0**](https://creativecommons.org/licenses/by/3.0/): [https://opengameart.org/content/space-ships-1](https://opengameart.org/content/space-ships-1)

## Music
- [Beepbox](https://www.beepbox.co) was used to compose the music in this game.
- [OpenMPT](https://openmpt.org/) was used to convert [MIDI](https://en.wikipedia.org/wiki/MIDI) versions of the music exported from [Beepbox](https://www.beepbox.co) to [Impulse](https://en.wikipedia.org/wiki/Impulse_Tracker) [Tracker](http://www.users.on.net/~jtlim/ImpulseTracker/) ```.it``` files to use with [Butano](https://github.com/GValiente/butano) (which uses [Maxmod](https://maxmod.devkitpro.org/) for mod tracker music playback). The actual music in-game gets its sound from [OpenMPT](https://openmpt.org/)'s included sound samples located at ```C:\Program Files\OpenMPT\ExampleSongs\Samples``` and/or from the GM.DLS library included with [Windows](https://en.wikipedia.org/wiki/Microsoft_Windows) which [OpenMPT](https://openmpt.org/) [uses by default](https://wiki.openmpt.org/Manual:_Tree_View#MIDI_Library) for giving [MIDI](https://en.wikipedia.org/wiki/MIDI) instruments within MIDI files sound.
