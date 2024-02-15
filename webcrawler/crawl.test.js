const { normalizeURL, getURLfromHTTP } = require("./crawl");
const { test, expect } = require("@jest/globals");

test("normalizeURL", () => {
  const input = "https://blog.boot.com/path/";
  const actual = normalizeURL(input);
  const expected = "blog.boot.com/path";
  expect(actual).toEqual(expected);
});

test("getURLsfromHTMl", () => {
  const inputHTMLBody = `
    <html>
        <body>
            <a href="http://google.com" target="_blank"/>
        </body>
    </html>
    `;
  const actual = getURLfromHTTP(inputHTMLBody);
  const expected = [`google.com`];
  expect(actual).toEqual(expected);
});
