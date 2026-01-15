# Warehouse Under Control

## Building

To build the main BFF service:

```bash
bazel build //web-app/bff:main
```

## IDE Setup (Intellisense)

This project uses [Hedron's Compile Commands Extractor](https://github.com/hedronvision/bazel-compile-commands-extractor) to generate `compile_commands.json` for VS Code / clangd support.

If you add new files or change dependencies, you need to refresh the compilation database so the IDE can resolve headers correctly.

Run the following command:

```bash
bazel run //:refresh_compile_commands
```

This will generate/update `compile_commands.json` in the workspace root.
