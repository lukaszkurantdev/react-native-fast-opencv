const withNextra = require('nextra')({
  theme: 'nextra-theme-docs',
  themeConfig: './theme.config.jsx',
});

module.exports = {
  ...withNextra(),
  basePath: '/react-native-fast-opencv',
  output: 'export',
  images: { unoptimized: true },
};
