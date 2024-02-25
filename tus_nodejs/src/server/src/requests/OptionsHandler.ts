import { MAX_AGE, TUS_RESUMABLE, TUS_VERSION } from "utils/src/CONSTANT";
import { BaseHandler } from "./BaseHandler";

import type http from "node:http"

// A successful response indicated by the 204 No Content or 200 OK status
// MUST contain the Tus - Version header.It MAY include the Tus - Extension and Tus - Max - Size headers.
class OptionsHandler extends BaseHandler {
  async send(req: http.IncomingMessage, res: http.ServerResponse) {
    const maxSize = this.getConfiguredMaxUploadSize();
    if (maxSize) {
      res.setHeader("Tus-Max-Size", maxSize);
    }
    res.setHeader("Access-Control-Max-Age", MAX_AGE)
    res.setHeader("Tus-Resumable", TUS_RESUMABLE)
    res.setHeader("Tus-Version", TUS_VERSION)
  }
}
