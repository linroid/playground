package com.linroid.weather;

import android.accounts.AbstractAccountAuthenticator;
import android.accounts.Account;
import android.accounts.AccountAuthenticatorResponse;
import android.accounts.NetworkErrorException;
import android.content.Context;
import android.os.Bundle;

import timber.log.Timber;

/**
 * Created by linroid on 1/25/15.
 */
public class Authenticator extends AbstractAccountAuthenticator {
    public Authenticator(Context context) {
        super(context);
    }

    @Override
    public Bundle editProperties(AccountAuthenticatorResponse response, String accountType) {
        Timber.i("editProperties, accountType:%s", accountType);
        return null;
    }

    @Override
    public Bundle addAccount(AccountAuthenticatorResponse response, String accountType, String authTokenType, String[] requiredFeatures, Bundle options) throws NetworkErrorException {
        Timber.i("addAccount, accountType:%s", accountType);

        return null;
    }

    @Override
    public Bundle confirmCredentials(AccountAuthenticatorResponse response, Account account, Bundle options) throws NetworkErrorException {
        Timber.i("confirmCredentials, options:%s", options.toString());

        return null;
    }

    @Override
    public Bundle getAuthToken(AccountAuthenticatorResponse response, Account account, String authTokenType, Bundle options) throws NetworkErrorException {
        Timber.i("getAuthToken, authTokenType:%s", authTokenType);

        return null;
    }

    @Override
    public String getAuthTokenLabel(String authTokenType) {
        Timber.i("getAuthTokenLabel, authTokenType:%s", authTokenType);

        return null;
    }

    @Override
    public Bundle updateCredentials(AccountAuthenticatorResponse response, Account account, String authTokenType, Bundle options) throws NetworkErrorException {
        Timber.i("updateCredentials, authTokenType:%s", authTokenType);

        return null;
    }

    @Override
    public Bundle hasFeatures(AccountAuthenticatorResponse response, Account account, String[] features) throws NetworkErrorException {
        Timber.i("hasFeatures, features:%s", features);

        return null;
    }
}
