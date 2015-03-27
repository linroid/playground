package com.linroid.weather;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.DialogFragment;
import android.text.TextUtils;
import android.widget.EditText;
import android.widget.Toast;

/**
 * Created by linroid on 1/25/15.
 */
public class AddCityFragment extends DialogFragment{
    private OnCityAddedListener listenter;
    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        final EditText cityInput = new EditText(getActivity());
        int padding = getResources().getDimensionPixelSize(R.dimen.padding_input);
        cityInput.setPadding(padding*2, padding, padding*2, padding);
        cityInput.setHint(R.string.hint_input_city);
        AlertDialog dialog = new AlertDialog.Builder(getActivity())
                .setTitle(R.string.title_add_city)
                .setView(cityInput)
                .setCancelable(true)
                .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        String cityName = cityInput.getText().toString();
                        if (TextUtils.isEmpty(cityName)) {
                            Toast.makeText(getActivity(), R.string.empty_city, Toast.LENGTH_SHORT).show();
                            cityInput.setError(getString(R.string.empty_city));
                            return;
                        }
                        addCity(cityName);
                    }
                })
                .setNegativeButton(android.R.string.cancel, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dismiss();
                    }
                })
                .create();
        return dialog;
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        listenter = (OnCityAddedListener) activity;
    }

    @Override
    public void onDetach() {
        super.onDetach();
        listenter = null;
    }

    private void addCity(String cityName) {
        if(listenter !=null){
            listenter.onAddCity(cityName);
        }
        dismiss();
    }
    public static interface OnCityAddedListener {
        void onAddCity(String name);
    }
}
