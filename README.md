# Bake

Bake is an alternative to GNU Make. Bake's syntax looks sexier, and is easier for beginners to learn.

# Why bake?

Well... to be honest, I don't really like Make, so I cooked Bake.

# How to cook

Cooking && Baking is easy! Here's how:

1. Download the file
2. Make an alias
3. Run it in the same directory as your Bakefile

# Making a Bakefile

Cooking is easy. Just make a file with the name (case sensitive) 'Bakefile.' The contents should be like this:

```

>cook{
    : echo "Some command" :
}

>serve{
    : echo "Command to execute on exot" :
}

```

The >cook{} function cooks the file, the >serve{} function serves the file (with whatever commands you defined for it.)

Bake is also not platform-shell specific. Features like a global 'clrscr' (clear screen) for both POSIX and Windows is coming soon!
