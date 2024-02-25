import type http from 'node:http'
import { DataStore } from "utils/src/DataStore";
import { BaseHandler } from "./BaseHandler";
import { ServerOptions } from '../../../types';

export class PatchHandler extends BaseHandler {

    constructor(
        options: ServerOptions,
        store: DataStore
    ) {
        super(options, store);
        this.store = store;
    }
    store: DataStore;

    /**
     * Write data to the DataStore and return the new offset.
    */
    async send(
        req: http.IncomingMessage,
        res: http.ServerResponse,
    ) {

    }
}