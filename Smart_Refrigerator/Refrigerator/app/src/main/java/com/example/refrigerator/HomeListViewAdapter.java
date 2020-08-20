package com.example.refrigerator;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.core.content.ContextCompat;

import java.util.ArrayList;

public class HomeListViewAdapter extends BaseAdapter {
    // Adapter에 추가된 데이터를 저장하기 위한 ArrayList
    private ArrayList<ListViewItem> listViewItemList = new ArrayList<ListViewItem>() ;

    // HomeListViewAdapter의 생성자
    public HomeListViewAdapter() {

    }

    // Adapter에 사용되는 데이터의 개수를 리턴. : 필수 구현
    @Override
    public int getCount() {
        return listViewItemList.size() ;
    }

    // position에 위치한 데이터를 화면에 출력하는데 사용될 View를 리턴. : 필수 구현
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        final int pos = position;
        final Context context = parent.getContext();

        // "listview_item" Layout을 inflate하여 convertView 참조 획득.
        if (convertView == null) {
            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = inflater.inflate(R.layout.listview_item, parent, false);
        }

        // 화면에 표시될 View(Layout이 inflate된)으로부터 위젯에 대한 참조 획득
        ImageView iconImageView = (ImageView) convertView.findViewById(R.id.imageView1) ;
        TextView nameView = (TextView) convertView.findViewById(R.id.textView6) ;
        TextView _idView = (TextView) convertView.findViewById(R.id.textView7) ;
        TextView findView = (TextView) convertView.findViewById(R.id.textView8) ;
        TextView expirationView = (TextView) convertView.findViewById(R.id.textView9) ;

        // Data Set(listViewItemList)에서 position에 위치한 데이터 참조 획득
        ListViewItem listViewItem = listViewItemList.get(position);

        // 아이템 내 각 위젯에 데이터 반영

        if(listViewItem.getFind().equals("야채")){
            iconImageView.setImageDrawable(ContextCompat.getDrawable(context.getApplicationContext(),R.drawable.vegetables));
        } else if(listViewItem.getFind().equals("과일")){
            iconImageView.setImageDrawable(ContextCompat.getDrawable(context.getApplicationContext(),R.drawable.fruit));
        } else if(listViewItem.getFind().equals("육류")){
            iconImageView.setImageDrawable(ContextCompat.getDrawable(context.getApplicationContext(),R.drawable.meat));
        } else if(listViewItem.getFind().equals("유제품")){
            iconImageView.setImageDrawable(ContextCompat.getDrawable(context.getApplicationContext(),R.drawable.milk));
        } else if(listViewItem.getFind().equals("곡식")){
            iconImageView.setImageDrawable(ContextCompat.getDrawable(context.getApplicationContext(),R.drawable.rice));
        } else if(listViewItem.getFind().equals("음주")){
            iconImageView.setImageDrawable(ContextCompat.getDrawable(context.getApplicationContext(),R.drawable.drink));
        } else if(listViewItem.getFind().equals("기타")||listViewItem.getFind().equals("분류선택")||listViewItem.getFind().equals("종류")){
            iconImageView.setImageDrawable(ContextCompat.getDrawable(context.getApplicationContext(),R.drawable.image));
        }

        nameView.setText(listViewItem.getName());
        _idView.setText(Integer.toString(listViewItem.get_id()));
        findView.setText(listViewItem.getFind());
        expirationView.setText(listViewItem.getExpiration());

        return convertView;
    }

    // 지정한 위치(position)에 있는 데이터와 관계된 아이템(row)의 ID를 리턴. : 필수 구현
    @Override
    public long getItemId(int position) {
        return position ;
    }

    // 지정한 위치(position)에 있는 데이터 리턴 : 필수 구현
    @Override
    public Object getItem(int position) {
        return listViewItemList.get(position);
    }

    // 아이템 데이터 추가를 위한 함수. 개발자가 원하는대로 작성 가능.
    public void addItem(Drawable icon, String name, int _id, String find, String expiration) {
        ListViewItem item = new ListViewItem();

        item.setIcon(icon);
        item.setName(name);
        item.set_id(_id);
        item.setFind(find);
        item.setExpiration(expiration);
        listViewItemList.add(item);
    }
}