import nextra from 'nextra';

const withNextra = nextra({});

/** @type {import('next').NextConfig} */
const nextConfig = {
  basePath: '/react-native-fast-opencv',
  output: 'export',
  images: { unoptimized: true },
  turbopack: { root: import.meta.dirname },
};

export default withNextra(nextConfig);
