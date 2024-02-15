"use strict";
const jsdom = require("jsdom");
const { JSDOM } = jsdom;

const getURLfromHTTP = (inputHTML, baseUrl) => {
  const urls = [];
  const dom = new JSDOM(inputHTML);
  const linkElements = dom.window.document.querySelectorAll("a");
  console.log(linkElements);
  for (const linkElement of linkElements) {
    urls.push(normalizeURL(linkElement.href));
  }
  console.log(urls);
  return urls;
};
const normalizeURL = (urlString) => {
  const urlObject = new URL(urlString);

  const hostPath = `${urlObject.hostname}${urlObject.pathname}`;
  if (hostPath.length > 0 && hostPath.slice(-1) === "/") {
    return hostPath.slice(0, -1);
  }
  return hostPath;
};

module.exports = {
  normalizeURL: normalizeURL,
  getURLfromHTTP: getURLfromHTTP,
};
