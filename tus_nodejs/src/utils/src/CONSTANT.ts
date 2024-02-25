export const MAX_UPLOAD_SIZE = 40000000 as const;
export const MAX_AGE = 86_400 as const
export const TUS_RESUMABLE = '1.0.0' as const
export const TUS_VERSION = ['1.0.0'] as const

export const ERRORS = {
    MISSING_OFFSET: {
        status_code: 403,
        body: 'Upload-Offset header required\n',
    },

    FILE_NOT_FOUND: {
        status_code: 404,
        body: 'The file for this url was not found\n',
    },
    FILE_NO_LONGER_EXISTS: {
        status_code: 410,
        body: 'The file for this url no longer exists\n',
    },

}