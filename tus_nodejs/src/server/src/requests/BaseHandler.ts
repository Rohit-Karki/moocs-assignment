import EventEmitter from "node:events"

import { ServerOptions } from "../../../types";

import type http from 'node:http'
import { DataStore } from "../../../utils/src/DataStore";
import { MAX_UPLOAD_SIZE } from './../../../utils/src/CONSTANT';

/*  This regular expression is designed to extract 
    the last part of a string, which represents a file ID in a URL or path. 
*/
const reExtractFileID = /([^/]+)\/?$/
const reForwardedHost = /host="?([^";]+)/
const reForwardedProto = /proto=(https?)/


export class BaseHandler {
  options: ServerOptions
  dataStore: DataStore

  constructor(
    options: ServerOptions,
    dataStore: DataStore
  ) {
    this.options = options
    this.dataStore = dataStore
  }
  getConfiguredMaxUploadSize() {
    return MAX_UPLOAD_SIZE;
  }
  async write(res: http.ServerResponse, status: number, headers = {}, body = '') {
    if (status != 204) {
      res.setHeader('content-length', Buffer.byteLength(body, 'utf-8'));
    }
    res.writeHead(status, headers);
    res.write(body);
    return res.end();
  }
  generateFileUrl(req: http.IncomingMessage, id: string): string {
    const path = this.options.path === '/' ? "" : this.options.path;
    if (this.options.generateUrl) {
      const { host, protocol } = this.extractHostandProto(req)
      return this.options.generateUrl(req, {
        protocol,
        host,
        path,
        id
      })
    }

    // Default implementation
    if (this.options.isRelative) {
      return `${path}/${id}`
    }
    const { host, protocol } = this.extractHostandProto(req)
    return `${protocol}://${host}/${id}`
  }

  protected extractHostandProto(req: http.IncomingMessage): { host: string, protocol: string } {
    let host
    let protocol

    if (this.options.respectForwardedHeaders) {
      const forwarded = req.headers.forwarded as string | undefined
      // If the options is to respect(use the forward header) then
      // that host and protocol is to be used
      if (forwarded) {
        host ??= reForwardedHost.exec(forwarded)?.[1]
        protocol ??= reForwardedProto.exec(forwarded)?.[1]
      }
      const forwardHost = req.headers['x-forwarded-host']
      const forwardProto = req.headers['x-forwarded-proto']

      // @ts-expect-error we can pass undefined
      if (['http', 'https'].includes(forwardProto)) {
        protocol ??= forwardProto
      }

      host ??= forwardHost
    }
    host ??= req.headers.host
    protocol ??= 'http'

    return {
      host: host as string,
      protocol: protocol as string
    }
  }
  getFileIdFromRequest(req: http.IncomingMessage) {
    // search through all the files to find the id of the request
    if (this.options.getFileIdFromUrl) {
      return this.options.getFileIdFromUrl(req)
    }
    const match = reExtractFileID.exec(req.url as string)
    if (!match || this.options.path.includes(match[1])) {
      return
    }
    // 
    /* In web development, decodeURIComponent is a JavaScript function that is used to decode a Uniform Resource Identifier(URI)
    component, previously created by the encodeURIComponent function.URIs, or URLs, can contain special characters such as
    spaces or non - ASCII characters, which need to be encoded for proper transmission.
    The decodeURIComponent function reverses this encoding process. */
    return decodeURIComponent(match[1])
  }

}
