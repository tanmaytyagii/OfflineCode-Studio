# Resources

Production assets are grouped by ownership:

```text
resources/
|-- icons/          # Original SVG sources and generated platform sizes
|-- themes/         # Semantic UI and syntax color tokens
|-- templates/      # Versioned project templates
|-- help/           # Packaged offline documentation
`-- translations/   # Qt translation sources
```

Every third-party asset requires a compatible license entry in the release notices. Prefer vector originals and generate raster variants during the build; do not commit editor metadata or unlicensed downloaded artwork.
