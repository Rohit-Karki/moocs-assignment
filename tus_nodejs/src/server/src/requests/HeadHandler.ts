import { BaseHandler } from "./BaseHandler";
import type http from 'node:http';

export class HeadHandler extends BaseHandler {
    // A HEAD request is used to determine the offset at which the upload should be continued.
    async getUploadOffset(
        req: http.IncomingMessage,
        res: http.ServerResponse
    ): Promise<number> {
        const fileId = this.getFileIdFromRequest(req);

        if (!fileId) {
            throw new Error("File id should be present")
        }
        if (this.options.onIncomingRequest) {
            this.options.onIncomingRequest(req, res, fileId);
        }
        const file = this.get
        /*
        If the server doesnot finds the file id in the filestore
        (i.e user tries to resume the upload of the file which has been deleted) then it must respond)
        with the 404 Not Found or 410 Gone status. The latter one SHOULD
        be used if the Server is keeping track of expired uploads.
        */
        const now = new Date();
        if(this.)
        const
    }
}