import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import {HttpClientModule} from "@angular/common/http";
import {AppRoutingModule} from "./app-routing/app-routing.module";
import {FormsModule, ReactiveFormsModule} from "@angular/forms";
import {BrowserAnimationsModule} from "@angular/platform-browser/animations";
import {RouterModule, ActivatedRoute, ParamMap} from "@angular/router";
import { MatInputModule} from "@angular/material/input";
import { MatSelectModule} from "@angular/material/select";
import { MatButtonModule} from "@angular/material/button";
import { MatCheckboxModule} from "@angular/material/checkbox";
import { MatChipsModule} from "@angular/material/chips";
import {MatTableModule} from "@angular/material/table";
import {MatPaginatorModule} from "@angular/material/paginator";
import {MatSortModule} from "@angular/material/sort";
import {MatMenuModule} from '@angular/material/menu';
import {
  MatIconModule,
} from '@angular/material/icon';
import { UsersComponent } from './users/users.component';
import { RegisterComponent } from './register/register.component';
import { LoginComponent } from './login/login.component';
import { UserListComponent } from './users/user-list/user-list.component';
import { UserAddComponent } from './users/user-add/user-add.component';
import { UserDeleteComponent } from './users/user-delete/user-delete.component';
import { UserUpdateComponent } from './users/user-update/user-update.component';
import { UserFilterComponent } from './users/user-filter/user-filter.component';

@NgModule({
  declarations: [
    AppComponent,
    UsersComponent,
    RegisterComponent,
    LoginComponent,
    UserListComponent,
    UserAddComponent,
    UserDeleteComponent,
    UserUpdateComponent,
    UserFilterComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    RouterModule,
    HttpClientModule,
    ReactiveFormsModule,
    BrowserAnimationsModule,
    ReactiveFormsModule,
    BrowserAnimationsModule,
    MatInputModule,
    MatButtonModule,
    MatSelectModule,
    MatCheckboxModule,
    MatChipsModule,
    MatTableModule,
    MatSortModule,
    MatPaginatorModule,
    MatMenuModule,
    MatIconModule,
    FormsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
