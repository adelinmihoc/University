import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import { UserListComponent } from './users/user-list/user-list.component';
import {RouterModule} from '@angular/router';
import {UserService} from './users/shared/user.service';
import { UsersComponent } from './users/users.component';
import {HttpClientModule} from '@angular/common/http';
import {AppRoutingModule} from './app-routing/app-routing.module';
import { UserAddComponent } from './users/user-add/user-add.component';
import { UserDeleteComponent } from './users/user-delete/user-delete.component';
import { UserUpdateComponent } from './users/user-update/user-update.component';
import { UserLookupComponent } from './users/user-lookup/user-lookup.component';
import { UserBrowseComponent } from './users/user-browse/user-browse.component';

@NgModule({
  declarations: [
    AppComponent,
    UserListComponent,
    UsersComponent,
    UserAddComponent,
    UserDeleteComponent,
    UserUpdateComponent,
    UserLookupComponent,
    UserBrowseComponent,
  ],
  imports: [
    BrowserModule,
    RouterModule,
    HttpClientModule,
    AppRoutingModule
  ],
  providers: [UserService],
  bootstrap: [AppComponent]
})
export class AppModule { }
