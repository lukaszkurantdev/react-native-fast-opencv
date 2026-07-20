import { Layout, Navbar, Footer } from 'nextra-theme-docs';
import { Head } from 'nextra/components';
import { getPageMap } from 'nextra/page-map';
import 'nextra-theme-docs/style.css';

const logo = (
  <span style={{ display: 'flex', alignItems: 'center', columnGap: 10 }}>
    <svg
      xmlns="http://www.w3.org/2000/svg"
      width="38.36"
      height="35.979"
      viewBox="0 0 38.36 35.979"
    >
      <g id="opencv-icon" transform="translate(0)">
        <path
          id="Path_16"
          data-name="Path 16"
          d="M-7.119,4.2A8.289,8.289,0,0,1-10.981-5.12a8.289,8.289,0,0,1,8.006-6.143A8.289,8.289,0,0,1,5.032-5.12,8.289,8.289,0,0,1,1.17,4.2l-2.5-4.323A3.3,3.3,0,0,0,.211-3.828,3.3,3.3,0,0,0-2.975-6.272,3.3,3.3,0,0,0-6.16-3.828,3.3,3.3,0,0,0-4.623-.119Z"
          transform="translate(23.58 11.263)"
          fill="#409ded"
        />
        <path
          id="Path_17"
          data-name="Path 17"
          d="M4.145,15.467a8.289,8.289,0,1,1,8.289,0l-2.5-4.323a3.3,3.3,0,1,0-3.3,0Z"
          transform="translate(38.36 32.945) rotate(180)"
          fill="#409ded"
        />
        <path
          id="Path_18"
          data-name="Path 18"
          d="M4.145,15.468a8.289,8.289,0,1,1,8.289,0l-2.5-4.323a3.3,3.3,0,1,0-3.3,0Z"
          transform="translate(8.29 35.979) rotate(-119.998)"
          fill="#409ded"
        />
      </g>
    </svg>
    <span style={{ fontWeight: '700' }}>React Native Fast OpenCV</span>
  </span>
);

export const metadata = {
  title: {
    template: '%s – React Native Fast OpenCV',
    default: 'React Native Fast OpenCV',
  },
  description: 'A powerful port of OpenCV for React Native.',
  icons: {
    icon: [
      { url: '/react-native-fast-opencv/favicon.svg', type: 'image/svg+xml' },
      { url: '/react-native-fast-opencv/favicon.png', type: 'image/png' },
    ],
  },
  openGraph: {
    title: 'React Native Fast OpenCV',
    description: 'A powerful port of OpenCV for React Native.',
  },
};

export default async function RootLayout({ children }) {
  const pageMap = await getPageMap();

  return (
    <html lang="en" dir="ltr" suppressHydrationWarning>
      <Head />
      <body>
        <Layout
          pageMap={pageMap}
          navbar={
            <Navbar
              logo={logo}
              projectLink="https://github.com/lukaszkurantdev/react-native-fast-opencv"
            />
          }
          footer={
            <Footer>
              MIT {new Date().getFullYear()} ©{' '}
              <a
                href="https://lukaszkurant.com"
                target="_blank"
                rel="noreferrer"
              >
                Lukasz Kurant
              </a>
              .
            </Footer>
          }
          docsRepositoryBase="https://github.com/lukaszkurantdev/react-native-fast-opencv"
        >
          {children}
        </Layout>
      </body>
    </html>
  );
}
