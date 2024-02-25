import { RedisClientType } from '@redis/client'
import { KVStore } from './types';
import { Upload } from './../Upload';
// Redis based config store

export class RedisKVStore<T = Upload> implements KVStore<T> {
    constructor(redis: RedisClientType) {
        this.redisClient = redis
    }
    redisClient: RedisClientType
    async get(key: string): Promise<T | undefined> {
        return this.deserialize(await this.redisClient.get(key))
    }
    async set(key: string, value: T) {
        await this.redisClient.set(key, this.serialize(value))
    }
    async delete(key: string) {
        await this.redisClient.delete(key)
    }
    async list?(): Promise<T[]> {
        return this.redisClient.list()
    }

    deserialize(upload: string | null): T | undefined {
        return upload ? JSON.parse(upload) : undefined
    }
    serialize(upload: T): string {
        return JSON.stringify(upload)
    }

}